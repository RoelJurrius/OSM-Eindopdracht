#ifndef sensor_mock_h
#define sensor_mock_h

#include <stdbool.h>
#include <stddef.h>

#define SENSORID1 1
#define SENSORID2 2

#define defaultBufferSize 12
#define MAXBUFERSIZE 128
#define sampleIntervalMs 100

struct circularBuffer {
  int values[MAXBUFERSIZE];
  size_t size;
  size_t head;
  size_t count;
  bool full;
};

struct runningStats {
  unsigned long count;
  double mean;
  double m2;
};

struct sensorData {
  struct circularBuffer buffer;
  struct runningStats stats;
};

void sensorsInit(void);
void sensorsSetActive(bool active);
bool sensorsIsActive(void);

void sensorsUpdate(unsigned long nowMs);

bool sensorsSetBufferSize(size_t newSize);

void sensorReset(int sensorId);
void sensorsInterruptReset(void);

bool sensorAddMeasurement(int sensorId, int value);

double sensorGetActual(int sensorId);
double sensorGetAvg(int sensorId);
double sensorGetStdev(int sensorId);

bool sensorBufferIsFull(int sensorId);
size_t sensorBufferCount(int sensorId);
size_t sensorBufferSize(void);

int sensorMockRead1(void);
int sensorMockRead2(void);

#endif