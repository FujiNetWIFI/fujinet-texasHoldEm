/**
 * @brief   Global variables for the Heathkit H89
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license gpl v. 3, see LICENSE for details
 */

#ifdef __H89__

// 80x24 seat layout around the oval rail (src/h89/graphics.c, rows 7-17,
// columns 16-63). Cards are 6x5 with a column between the two hole cards, so
// a hand is 13 wide; a right-side seat's X is its right card, the other card
// 7 to the left. Top seats (cards rows 2-6) and the bottom-centre seat (YOU,
// rows 18-22) sit outside the rail, the side seats left and right of it.
// Each seat's move and bet lie on the felt just inside the rail in front of
// it, except the top-centre seat's, which sit beside its cards: the community
// board fills the felt below it. The pot and street label are below the
// board.
unsigned char playerXMaster[] = { 33, 2, 2, 5, 33, 69, 72, 72 };
unsigned char playerYMaster[] = { 18, 17, 10, 2, 2, 2, 10, 17 };

char playerDirMaster[] = { 1, 1, 1, 1, 1, -1, -1, -1 };
char playerBetXMaster[] = { 12, 16, 16, 13, 14, -7, -10, -10 };
char playerBetYMaster[] = { -3, -2, 1, 6, 1, 6, 1, -2 };

//                               2                3                4
char playerCountIndex[] = {0,4,0,0,0,0,0,0, 0,2,6,0,0,0,0,0, 0,2,4,6,0,0,0,0,
// 5                6                 7                8
    0,2,3,5,6,0,0,0, 0,2,3,4,5,6,0,0,  0,2,3,4,5,6,7,0, 0,1,2,3,4,5,6,7};

#endif /* __H89__ */
