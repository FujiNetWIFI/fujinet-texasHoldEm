#ifdef __TRS80M2__

// Two 4-wide cards with a column between take 9 columns; a right-side seat's
// X is its right card. Seats sit down each side on rows 3, 10 and 17, with
// YOU bottom centre and one seat top centre, around the board (rows 9-12,
// columns 28-51). Each seat's move and bet are beside its cards, toward the
// middle.
unsigned char playerXMaster[] = { 36, 2, 2, 2, 36, 74, 74, 74 };
unsigned char playerYMaster[] = { 18, 17, 10, 3, 3, 3, 10, 17 };

char playerDirMaster[] = { 1, 1, 1, 1, 1, -1, -1, -1 };
char playerBetXMaster[] = { 11, 11, 11, 11, 11, -6, -6, -6 };
char playerBetYMaster[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// Seats to use for each player count, indexes into the arrays above
//                               2                3                4
char playerCountIndex[] = {0,4,0,0,0,0,0,0, 0,2,6,0,0,0,0,0, 0,2,4,6,0,0,0,0,
// 5                6                 7                8
   0,2,3,5,6,0,0,0, 0,2,3,4,5,6,0,0,  0,2,3,4,5,6,7,0, 0,1,2,3,4,5,6,7};

#endif /* __TRS80M2__ */
