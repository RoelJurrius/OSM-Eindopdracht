# GENERATION SEED:
# 42

import requests
import requests_raw
import sys
import os

key = 'ip'

def address():
    if key in os.environ:
        return "http://" + os.environ[key]

    raise ValueError(
        "set {} IP addres in {} environment variable".format(key, key))


def single_value_1():
  unit_test_name = "single value 1"
  req = "\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/1 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
10"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
228"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/1/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 228.0) <= 0.1

  req = "GET /sensors/1/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 0.0) <= 0.1

  req = "GET /sensors/1/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 228.0) <= 0.1

  print("OK {}".format(unit_test_name))

def single_value_2():
  unit_test_name = "single value 2"
  req = "\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/2 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
10"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
51"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/2/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 51.0) <= 0.1

  req = "GET /sensors/2/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 0.0) <= 0.1

  req = "GET /sensors/2/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 51.0) <= 0.1

  print("OK {}".format(unit_test_name))

def multiple_values():
  unit_test_name = "multiple values"
  req = "\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/1 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/2 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
14"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
501"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
457"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
285"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
209"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
178"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
864"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
65"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
61"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
191"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
447"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
476"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
54"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
407"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
859"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/1/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 361.0) <= 0.1

  req = "GET /sensors/1/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 255.74820206043063) <= 0.1

  req = "GET /sensors/1/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 361.0) <= 0.1

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
451"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
919"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
569"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
13"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
326"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
865"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
696"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/2/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 548.4285714285714) <= 0.1

  req = "GET /sensors/2/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 294.0825234729954) <= 0.1

  req = "GET /sensors/2/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 548.4285714285714) <= 0.1

  print("OK {}".format(unit_test_name))

def cbuff_overflow_1():
  unit_test_name = "cbuff overflow 1"
  req = "\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/1 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
5"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
318"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
440"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
689"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
209"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
189"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
778"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
198"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/1/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 403.0) <= 0.1

  req = "GET /sensors/1/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 225.6647323543744) <= 0.1

  req = "GET /sensors/1/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 412.6) <= 0.1

  print("OK {}".format(unit_test_name))

def cbuff_overflow_2():
  unit_test_name = "cbuff overflow 2"
  req = "\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/2 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
6"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
704"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
541"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
88"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
940"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
255"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
775"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
161"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
600"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/2/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 508.0) <= 0.1

  req = "GET /sensors/2/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 288.68235138296905) <= 0.1

  req = "GET /sensors/2/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 469.8333333333333) <= 0.1

  print("OK {}".format(unit_test_name))

def complete():
  unit_test_name = "complete"
  req = "\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/1 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/2 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
4"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
740"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
393"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
142"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
93"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/1/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 342.0) <= 0.1

  req = "GET /sensors/1/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 256.4205529983897) <= 0.1

  req = "GET /sensors/1/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 342.0) <= 0.1

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
466"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
592"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
163"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
476"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
206"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
778"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
569"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/2 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
928"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
747"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
333"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
758"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
727"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
429"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
546"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
146"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
350"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/2/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 551.5555555555555) <= 0.1

  req = "GET /sensors/2/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 240.65332885991418) <= 0.1

  req = "GET /sensors/2/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 367.75) <= 0.1

  req = "\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
501"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/1/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 373.8) <= 0.1

  req = "GET /sensors/1/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 501) <= 0.1

  print("OK {}".format(unit_test_name))

def error_no_values():
  unit_test_name = "error no values"
  req = "\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /sensors/1 HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
3"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /sensors/1/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - -1) <= 0.1

  req = "GET /sensors/1/stdev HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - -1) <= 0.1

  req = "GET /sensors/1/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - -1) <= 0.1

  print("OK {}".format(unit_test_name))

def error_404_post():
  unit_test_name = "error 404 post"
  req = "\
POST /sensors/3 HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
0"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 404

  print("OK {}".format(unit_test_name))

def error_404_get():
  unit_test_name = "error 404 get"
  req = "GET /sensors/3/avg HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 404
  if response.status_code == 200:
    assert abs(float(response.content.decode('ascii')) - 0) <= 0.1

  print("OK {}".format(unit_test_name))

def error_400_invalid_verb():
  unit_test_name = "error 400 invalid verb"
  req = "IOT /sensors/1/actual HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 400

  print("OK {}".format(unit_test_name))

def ok_get_200():
  unit_test_name = "ok get 200"
  req = "GET / HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200

  print("OK {}".format(unit_test_name))

def test_the_acceptation_test_setup():
  ok_get_200()

def the_real_acceptation_tests():
  single_value_1()
  single_value_2()
  multiple_values()
  cbuff_overflow_1()
  cbuff_overflow_2()
  complete()
  error_no_values()
  error_404_post()
  error_404_get()
  error_400_invalid_verb()

if __name__ == "__main__":
  # change to the_real_acceptation_tests() as soon as you've successfully
  # ran the initial acceptation tests
  test_the_acceptation_test_setup()
