#ifndef request_h
#define request_h

#include <stdbool.h>
#include <stdint.h>

/*
Je parseert requests gebaseerd op code die is geschreven op
basis van een ABNF definitie.

Wanneer je in een situatie zit met minder beperkingen (met
name, werkgeheugen) zou je van de ABNF elementen een boom
bouwen waarin je later gegevens op kan halen.

We kiezen nu voor een pragmatischer benadering: met de op
ABNF gebaseerde functies geef je een verwijzing naar een
`struct request` mee, zodat je daar relevante gegevens in
kan schrijven.

Onderstaande is een SUGGESTIE. Je bent vrij een andere
indeling te kiezen. Een eerdere variant is getest. In
onderstaande variant heb ik een aantal wijzigingen staan die
beter passen bij de structuur van de ABNF. Ik heb die
wijzigingen onvoldoende getest. Het kan zijn dat je alsnog
wat kleine zaken moet wijzigen.
*/

enum method {
  METHOD_UNRECOGNIZED,
  METHOD_GET,
  METHOD_POST,
  METHOD_PUT,
  METHOD_DELETE
};

enum target {
  TARGET_UNRECOGNIZED,
  TARGET_CONFIG,
  TARGET_MODE,
  TARGET_CBUFFSIZE,
  TARGET_SENSORS,
  TARGET_1,
  TARGET_2,
  TARGET_AVG,
  TARGET_STDEV,
  TARGET_ACTUAL
};

enum field { FIELD_UNRECOGNIZED, FIELD_CONTENT_LENGTH };

enum body {
  BODY_EMPTY,
  BODY_UNRECOGNIZED,
  BODY_PASSIVE,
  BODY_ACTIVE,
  BODY_INT
};

struct request {
  bool success;

  enum method method;
  enum target target[3];
  enum field field;
  enum body body;

  int16_t content_length;

  int16_t body_int; // in case body == BODY_INT
};

#endif