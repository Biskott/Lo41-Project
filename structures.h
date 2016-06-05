#ifndef STRUCTURES_H
#define	STRUCTURES_H

typedef enum {
    EO,
    OE
} Direction;

typedef struct {
    char *nom;
    Direction direction;
    int priorite;
} Train;



#endif	/* STRUCTURES_H */
