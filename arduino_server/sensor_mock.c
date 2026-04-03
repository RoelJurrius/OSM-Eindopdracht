#include "sensor_mock.h"
#include <math.h>
#include <stdlib.h>

#ifndef ARDUINO
static int hostRandom(int minInclusive, int maxExclusive) {
  int span = maxExclusive - minInclusive;

  if (span <= 0) {
    return minInclusive;
  }

  return minInclusive + (rand() % span);
}
#endif

static struct sensorData sensor1;
static struct sensorData sensor2;

static bool activeMode = true;
static unsigned long lastSampleMs = 0UL;
static size_t currentBufferSize = defaultBufferSize;

static double round1(double value);
static struct sensorData* getSensor(int sensorId);

static void circularBufferInit(struct circularBuffer* cb,
                               size_t size);
static void circularBufferClear(struct circularBuffer* cb);
static bool circularBufferResize(struct circularBuffer* cb,
                                 size_t size);
static void circularBufferPush(struct circularBuffer* cb,
                               int value);
static double
circularBufferAverage(const struct circularBuffer* cb);

static void runningStatsInit(struct runningStats* stats);
static void runningStatsReset(struct runningStats* stats);
static void runningStatsAdd(struct runningStats* stats,
                            int value);
static double
runningStatsMean(const struct runningStats* stats);
static double
runningStatsStdev(const struct runningStats* stats);

static double round1(double value) {
  if (value >= 0.0) {
    return floor(value * 10.0 + 0.5) / 10.0;
  }
  return ceil(value * 10.0 - 0.5) / 10.0;
}

static struct sensorData* getSensor(int sensorId) {
  if (sensorId == SENSORID1) {
    return &sensor1;
  }
  if (sensorId == SENSORID2) {
    return &sensor2;
  }
  return NULL;
}

static void circularBufferInit(struct circularBuffer* cb,
                               size_t size) {
  cb->size = size;
  cb->head = 0U;
  cb->count = 0U;
  cb->full = false;
}

static void circularBufferClear(struct circularBuffer* cb) {
  cb->head = 0U;
  cb->count = 0U;
  cb->full = false;
}

static bool circularBufferResize(struct circularBuffer* cb,
                                 size_t size) {
  if (size == 0U || size > MAXBUFERSIZE) {
    return false;
  }

  cb->size = size;
  cb->head = 0U;
  cb->count = 0U;
  cb->full = false;
  return true;
}

static void circularBufferPush(struct circularBuffer* cb,
                               int value) {
  cb->values[cb->head] = value;
  cb->head = (cb->head + 1U) % cb->size;

  if (cb->count < cb->size) {
    cb->count++;
  }

  if (cb->count == cb->size) {
    cb->full = true;
  }
}

static double
circularBufferAverage(const struct circularBuffer* cb) {
  size_t i;
  size_t start;
  double sum = 0.0;

  if (cb->count == 0U) {
    return 0.0;
  }

  start = (cb->head + cb->size - cb->count) % cb->size;

  for (i = 0U; i < cb->count; i++) {
    size_t index = (start + i) % cb->size;
    sum += (double)cb->values[index];
  }

  return sum / (double)cb->count;
}

static void runningStatsInit(struct runningStats* stats) {
  stats->count = 0UL;
  stats->mean = 0.0;
  stats->m2 = 0.0;
}

static void runningStatsReset(struct runningStats* stats) {
  runningStatsInit(stats);
}

static void runningStatsAdd(struct runningStats* stats,
                            int value) {
  double x = (double)value;
  double delta;
  double delta2;

  stats->count++;
  delta = x - stats->mean;
  stats->mean += delta / (double)stats->count;
  delta2 = x - stats->mean;
  stats->m2 += delta * delta2;
}

static double
runningStatsMean(const struct runningStats* stats) {
  if (stats->count == 0UL) {
    return 0.0;
  }
  return stats->mean;
}

static double
runningStatsStdev(const struct runningStats* stats) {
  if (stats->count < 2UL) {
    return 0.0;
  }
  return sqrt(stats->m2 / (double)stats->count);
}

void sensorsInit(void) {
  currentBufferSize = defaultBufferSize;
  activeMode = true;
  lastSampleMs = 0UL;

  circularBufferInit(&sensor1.buffer, defaultBufferSize);
  circularBufferInit(&sensor2.buffer, defaultBufferSize);
  runningStatsInit(&sensor1.stats);
  runningStatsInit(&sensor2.stats);
}

void sensorsSetActive(bool active) { activeMode = active; }

bool sensorsIsActive(void) { return activeMode; }

void sensorsUpdate(unsigned long nowMs) {
  if (!activeMode) {
    return;
  }

  if ((nowMs - lastSampleMs) < sampleIntervalMs) {
    return;
  }

  lastSampleMs = nowMs;
  sensorAddMeasurement(SENSORID1, sensorMockRead1());
  sensorAddMeasurement(SENSORID2, sensorMockRead2());
}

bool sensorsSetBufferSize(size_t newSize) {
  bool ok1;
  bool ok2;

  if (newSize == 0U || newSize > MAXBUFERSIZE) {
    return false;
  }

  ok1 = circularBufferResize(&sensor1.buffer, newSize);
  ok2 = circularBufferResize(&sensor2.buffer, newSize);

  if (!(ok1 && ok2)) {
    return false;
  }

  currentBufferSize = newSize;
  return true;
}

void sensorReset(int sensorId) {
  struct sensorData* sensor = getSensor(sensorId);

  if (sensor == NULL) {
    return;
  }

  circularBufferClear(&sensor->buffer);
  runningStatsReset(&sensor->stats);
}

void sensorsInterruptReset(void) {
  runningStatsReset(&sensor1.stats);
  runningStatsReset(&sensor2.stats);

  circularBufferResize(&sensor1.buffer, defaultBufferSize);
  circularBufferResize(&sensor2.buffer, defaultBufferSize);

  currentBufferSize = defaultBufferSize;
}

bool sensorAddMeasurement(int sensorId, int value) {
  struct sensorData* sensor = getSensor(sensorId);

  if (sensor == NULL) {
    return false;
  }

  if (value < 0 || value > 1023) {
    return false;
  }

  circularBufferPush(&sensor->buffer, value);
  runningStatsAdd(&sensor->stats, value);
  return true;
}

double sensorGetActual(int sensorId) {
  struct sensorData* sensor = getSensor(sensorId);
  double avg;

  if (sensor == NULL) {
    return 0.0;
  }

  avg = circularBufferAverage(&sensor->buffer);
  circularBufferClear(&sensor->buffer);
  return round1(avg);
}

double sensorGetAvg(int sensorId) {
  struct sensorData* sensor = getSensor(sensorId);

  if (sensor == NULL) {
    return 0.0;
  }

  return round1(runningStatsMean(&sensor->stats));
}

double sensorGetStdev(int sensorId) {
  struct sensorData* sensor = getSensor(sensorId);

  if (sensor == NULL) {
    return 0.0;
  }

  return round1(runningStatsStdev(&sensor->stats));
}

unsigned long sensorStatsCount(int sensorId) {
  struct sensorData* sensor = getSensor(sensorId);

  if (sensor == NULL) {
    return 0UL;
  }

  return sensor->stats.count;
}

bool sensorBufferIsFull(int sensorId) {
  struct sensorData* sensor = getSensor(sensorId);

  if (sensor == NULL) {
    return false;
  }

  return sensor->buffer.full;
}

size_t sensorBufferCount(int sensorId) {
  struct sensorData* sensor = getSensor(sensorId);

  if (sensor == NULL) {
    return 0U;
  }

  return sensor->buffer.count;
}

size_t sensorBufferSize(void) { return currentBufferSize; }

int sensorMockRead1(void) { return (int)(rand() % 1024); }

int sensorMockRead2(void) { return (int)(rand() % 1024); }
