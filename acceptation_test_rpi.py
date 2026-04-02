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


def rasperry_pi_server_integration_0():
  unit_test_name = "rasperry pi server integration 0"
  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 6\r\n\
\r\n\
51 285"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
563 209"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
501 178"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
457 864"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 6\r\n\
\r\n\
61 476"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 6\r\n\
\r\n\
191 54"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
447 407"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  b0, b1, b2, R2 = response.content.decode('ascii').split(' ')
  assert abs(float(b0) - 813.6179109891931) <= 0.1
  assert abs(float(b1) - -6.265623131725841) <= 0.1
  assert abs(float(b2) - 0.011982020974491935) <= 0.1
  assert abs(float(R2) - 1.0) <= 0.1

  print("OK {}".format(unit_test_name))

def rasperry_pi_server_integration_1():
  unit_test_name = "rasperry pi server integration 1"
  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
451 440"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
919 689"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
569 209"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 6\r\n\
\r\n\
13 189"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
326 778"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
865 198"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
696 735"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
569 704"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
318 541"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
940 161"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
255 600"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
775 740"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  b0, b1, b2, R2 = response.content.decode('ascii').split(' ')
  assert abs(float(b0) - -558.7134398448466) <= 0.1
  assert abs(float(b1) - 5.950502781889705) <= 0.1
  assert abs(float(b2) - -0.0055157980705425914) <= 0.1
  assert abs(float(R2) - 1.0) <= 0.1

  print("OK {}".format(unit_test_name))

def rasperry_pi_server_integration_2():
  unit_test_name = "rasperry pi server integration 2"
  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
142 206"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 6\r\n\
\r\n\
93 778"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
466 569"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
592 928"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
163 747"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
476 333"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
727 777"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
429 552"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
546 449"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
146 664"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
350 114"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
501 469"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 6\r\n\
\r\n\
334 65"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
946 646"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  b0, b1, b2, R2 = response.content.decode('ascii').split(' ')
  assert abs(float(b0) - 543.118382806753) <= 0.1
  assert abs(float(b1) - -0.869884430355276) <= 0.1
  assert abs(float(b2) - 0.001182567433712895) <= 0.1
  assert abs(float(R2) - 0.27912618643455545) <= 0.1

  print("OK {}".format(unit_test_name))

def rasperry_pi_server_integration_3():
  unit_test_name = "rasperry pi server integration 3"
  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
548 542"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
135 285"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
432 505"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
644 538"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
435 877"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 8\r\n\
\r\n\
1022 817"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
810 741"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
939 449"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
292 283"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
186 514"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 5\r\n\
\r\n\
96 23"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
224 234"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
313 546"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
327 696"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
864 228"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
130 601"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
788 890"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
781 323"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
958 929"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  b0, b1, b2, R2 = response.content.decode('ascii').split(' ')
  assert abs(float(b0) - 243.34641453096052) <= 0.1
  assert abs(float(b1) - 0.9646319218006107) <= 0.1
  assert abs(float(b2) - -0.0006077331371151136) <= 0.1
  assert abs(float(R2) - 0.15520557773892263) <= 0.1

  print("OK {}".format(unit_test_name))

def rasperry_pi_server_integration_4():
  unit_test_name = "rasperry pi server integration 4"
  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
539 611"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
365 407"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
217 313"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "DELETE /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
330 490"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 5\r\n\
\r\n\
1 118"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
663 493"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 8\r\n\
\r\n\
1000 161"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 6\r\n\
\r\n\
39 175"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
229 995"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
743 141"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "\
POST /data HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
629 257"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 201

  req = "GET /statistics HTTP/1.0\r\n\r\n"
  response = requests_raw.raw(url=address(), data=req)
  assert response.status_code == 200
  b0, b1, b2, R2 = response.content.decode('ascii').split(' ')
  assert abs(float(b0) - 254.8274328050184) <= 0.1
  assert abs(float(b1) - 1.3281138680146172) <= 0.1
  assert abs(float(b2) - -0.00158227145948518) <= 0.1
  assert abs(float(R2) - 0.31713908902848054) <= 0.1

  print("OK {}".format(unit_test_name))

def main():
  rasperry_pi_server_integration_0()
  rasperry_pi_server_integration_1()
  rasperry_pi_server_integration_2()
  rasperry_pi_server_integration_3()
  rasperry_pi_server_integration_4()


if __name__ == "__main__":
  main()
