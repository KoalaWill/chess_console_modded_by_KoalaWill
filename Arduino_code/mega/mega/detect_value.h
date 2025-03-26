const int group_nums[14][16] ={{0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650},
                              {0, 276, 297, 317, 352, 487, 461, 484, 474, 496, 507, 594, 586, 577, 563, 650}};
int i_to_places[16][4] = {{0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}, {1,1,0,0}, {1,0,1,0}, {1,0,0,1}, {0,1,1,0}, {0,1,0,1}, {0,0,1,1}, {0,1,1,1}, {1,0,1,1}, {1,1,0,1}, {1,1,1,0}, {1,1,1,1}};
int Group_places[14][4] = {{1,1,0,0}, {0,0,1,1}, {1,1,0,0}, {0,0,1,1}, {1,1,0,0}, {0,0,1,1}, {1,1,0,0}, {0,0,1,1}, {1,1,0,0}, {0,0,1,1}, {1,1,0,0}, {0,0,1,1}, {1,1,0,0}, {0,0,1,1}};
int temp_group[4];
int Groups[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char Alpha_moved;
int Num_moved;
char Alpha_placed;
int Num_placed;
String move = "   ";

void GroupPosDetecter(int num, int input) {
  if(input != Groups[num]) {
    for(int i=0; i<16; i++) {
      if(input == group_nums[num][i]) {
        for(int j=0; j<4; j++) {
          if(Group_places[num][j] == 1 && i_to_places[i][j] == 0) {
            if(num == 0) {Alpha_moved = 'a'; Num_moved = 8-j;}
            if(num == 1) {Alpha_moved = 'a'; Num_moved = 4-j;}
            if(num == 2) {Alpha_moved = 'b'; Num_moved = 8-j;}
            if(num == 3) {Alpha_moved = 'b'; Num_moved = 4-j;}
            if(num == 4) {Alpha_moved = 'c'; Num_moved = 8-j;}
            if(num == 5) {Alpha_moved = 'c'; Num_moved = 4-j;}
            if(num == 6) {Alpha_moved = 'd'; Num_moved = 8-j;}
            if(num == 7) {Alpha_moved = 'd'; Num_moved = 4-j;}
            if(num == 8) {Alpha_moved = 'e'; Num_moved = 8-j;}
            if(num == 9) {Alpha_moved = 'e'; Num_moved = 4-j;}
            if(num == 10) {Alpha_moved = 'f'; Num_moved = 8-j;}
            if(num == 11) {Alpha_moved = 'f'; Num_moved = 4-j;}
            if(num == 12) {Alpha_moved = 'g'; Num_moved = 8-j;}
            if(num == 13) {Alpha_moved = 'g'; Num_moved = 4-j;} 
          }
          if(Group_places[num][j] == 0 && i_to_places[j] == 1) {
            if(num == 0) {Alpha_placed = 'a'; Num_placed = 8-j;}
            if(num == 1) {Alpha_placed = 'a'; Num_placed = 4-j;}
            if(num == 2) {Alpha_placed = 'b'; Num_placed = 8-j;}
            if(num == 3) {Alpha_placed = 'b'; Num_placed = 4-j;}
            if(num == 4) {Alpha_placed = 'c'; Num_placed = 8-j;}
            if(num == 5) {Alpha_placed = 'c'; Num_placed = 4-j;}
            if(num == 6) {Alpha_placed = 'd'; Num_placed = 8-j;}
            if(num == 7) {Alpha_placed = 'd'; Num_placed = 4-j;}
            if(num == 8) {Alpha_placed = 'e'; Num_placed = 8-j;}
            if(num == 9) {Alpha_placed = 'e'; Num_placed = 4-j;}
            if(num == 10) {Alpha_placed = 'f'; Num_placed = 8-j;}
            if(num == 11) {Alpha_placed = 'f'; Num_placed = 4-j;}
            if(num == 12) {Alpha_placed = 'g'; Num_placed = 8-j;}
            if(num == 13) {Alpha_placed = 'g'; Num_placed = 8-j;}
          }
        }
      }
    }
  }
}

void BoardSetup() {
  Groups[0] = analogRead(A0);
  Groups[1] = analogRead(A1);
  Groups[2] = analogRead(A2);
  Groups[3] = analogRead(A3);
  Groups[4] = analogRead(A4);
  Groups[5] = analogRead(A5);
  Groups[6] = analogRead(A6);
  Groups[7] = analogRead(A7);
  Groups[8] = analogRead(A8);
  Groups[9] = analogRead(A9);
  Groups[10] = analogRead(A10);
  Groups[11] = analogRead(A11);
  Groups[12] = analogRead(A12);
  Groups[13] = analogRead(A13);
}

String BoardDetector() { // Function to read 
  GroupPosDetecter(0, analogRead(A0));
  GroupPosDetecter(1, analogRead(A1));
  GroupPosDetecter(2, analogRead(A2));
  GroupPosDetecter(3, analogRead(A3));
  GroupPosDetecter(4, analogRead(A4));
  GroupPosDetecter(5, analogRead(A5));
  GroupPosDetecter(6, analogRead(A6));
  GroupPosDetecter(7, analogRead(A7));
  GroupPosDetecter(8, analogRead(A8));
  GroupPosDetecter(9, analogRead(A9));
  GroupPosDetecter(10, analogRead(A10));
  GroupPosDetecter(11, analogRead(A11));
  GroupPosDetecter(12, analogRead(A12));
  GroupPosDetecter(13, analogRead(A13));
  Groups[0] = analogRead(A0);
  Groups[1] = analogRead(A1);
  Groups[2] = analogRead(A2);
  Groups[3] = analogRead(A3);
  Groups[4] = analogRead(A4);
  Groups[5] = analogRead(A5);
  Groups[6] = analogRead(A6);
  Groups[7] = analogRead(A7);
  Groups[8] = analogRead(A8);
  Groups[9] = analogRead(A9);
  Groups[10] = analogRead(A10);
  Groups[11] = analogRead(A11);
  Groups[12] = analogRead(A12);
  Groups[13] = analogRead(A13);
  move[0] = Alpha_moved;
  move[1] = '0'+ Num_moved;
  move[2] = Alpha_placed;
  move[3] = '0'+ Num_placed;
  return move;
}