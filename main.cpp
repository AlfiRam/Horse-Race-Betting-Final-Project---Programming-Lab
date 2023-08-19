#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cctype>
#include <string>
#include <unistd.h>
#include <time.h>
#include<windows.h>


#define NUM 15
#define MAX 50
using namespace std;

void mergeArr(int arr[], int start, int mid, int end)
{
  int n0 = mid - start + 1;
  int n1 = end - mid;
  int tempL[MAX], tempR[MAX];

  for (int i = 0; i < n0; i++)
      tempL[i] = arr[start + i];
  for (int j = 0; j < n1; j++)
      tempR[j] = arr[mid + 1 + j];

  int i = 0;
  int j = 0;
  int k = start;

  while (i < n0 && j < n1) {
      if (tempL[i] > tempR[j]) {
          arr[k] = tempL[i];
          i++;
      }
      else
      {
          arr[k] = tempR[j];
          j++;
      }
      k++;
  }

  while (i < n0) {
      arr[k] = tempL[i];
      i++;
      k++;
  }

  while (j < n1) {
      arr[k] = tempR[j];
      j++;
      k++;
  }
}

void sortArr(int arr[], int start, int end)
{
  if (start >= end)
      return;
  int mid = start + (end - start) / 2;
  sortArr(arr, start, mid);
  sortArr(arr, mid + 1, end);
  mergeArr(arr, start, mid, end);
}

int searchArr(int arr[], int start, int end, int find)
{
  int rec;
  if (start < end) {
      if (arr[start] == find)
          return start;
      else
          start++;
          rec = searchArr(arr, start, end, find);
  }
  else
      return -1;
  return rec;
}

int position(int pos, int horseNum)
{
  pos = pos + rand() % 5 + 1; // horse moves between 1 to 5 then outputs distance
  cout << horseNum << "[" << pos << "]: ";
  for (int b = 0; b <= pos; b++) 
      cout << "_";
  cout << " ~n-n^";
  cout << endl << endl;
  return pos;
}

void Start_Race(int horse_dist[], int horse_num, int Horses, int bet_type) 
{
  int pos[NUM];

  for (int i = 0; i < NUM; i++)
    pos[i] = 0;
    
  srand(time(NULL)); //randomises rand()

  for (int a = 0;a <= 50;a++) {

      system("cls");
      cout << "Horse Race Begin ! Support your Horse ! \n \n";

      for (int i = 0; i < Horses; i++)
      {
          pos[i] = position(pos[i], i + 1); // updates all horses position
      }

      int Leading = 0;

      for (int p = 0;p < Horses;p++)
      {
          horse_dist[p] = pos[p];
          if (horse_dist[p] > horse_dist[Leading])
              Leading = p;
      }

      cout << "Leading Horse: Horse #" << Leading + 1 << endl;

      unsigned int millisecond = 1000;
      Sleep(0.5 * millisecond); //sleeps for 0.5 second
  }
}

void Copy_Arr(int arr[], int arr2[], int start, int end) // copies arr to arr2
{
    for (int i = start; i < end; i++) 
        arr2[i] = arr[i];
}

void display_diff_level()
{
  cout << "Select Difficulty (1, 2 or 3): " << endl;
  cout << endl;
  cout << "1. EASY: 5 horses in race " << endl;
  cout << "2. MEDIUM: 10 horses in race " << endl;
  cout << "3. HARD: 15 horses in race " << endl;
  cout << endl;
}

void display_bet_type()
{
  cout << "Select Bet Type, You Have an Initial Budget of $100";
  cout << endl;
  cout << "1. Finish in 1st Place (win double)" << endl;
  cout << "2. Finish in the Top 2 (win 1/2)" << endl;
  cout << "3. Finish in the Top 3 (win 1/3)" << endl;
  cout << endl;
}

void input_bet(float &bet_amount, float &total_money)
{
  do {
      cout << "How much money would you like to put in? *MINIMUM IS $10, FOR 1ST ATTEMPT, MAX IS $100" << endl;
      cin >> bet_amount;
  } while (bet_amount < 10 || bet_amount > total_money);
  total_money = total_money - bet_amount;
}
void display_bet_result(int &bet_type, float &bet_amount, float &total_money, bool win)
{
    cout << endl << "Your Initial Bet Was $" << bet_amount<<endl;
  if (win) 
  {
    switch(bet_type)
    {
    case 1 : 
      cout << "You Have Won $" << bet_amount<<endl;
      total_money += bet_amount * 2; break;
    case 2 :
      cout << "You Have Won $" << bet_amount * 0.5<<endl;
      total_money += bet_amount * 1.5; break;
    case 3 :
      cout << "You Have Won $" << bet_amount * 0.33<<endl;
      total_money += bet_amount * 1.33; break;
    }
  }
  else
    cout << "You Have Lost $" << bet_amount<<endl;
  cout << "Your Money Now is $" << total_money<<endl;
}

bool Check_Win(int horse_perf[], int sorted_dist[], int betType, int bethorse)
{
  if (horse_perf[bethorse] >= sorted_dist[betType])
    return true;
  else
    return false;
}

void PrintArr (int arr[], int start, int max)
{
  for (int i = start; i < max; i++)
    cout << arr[i] << ", ";
  cout << endl;
}

void DisplayRaceResults (int horses, int horse_perf[], int sorted_dist[], int horse_num)
{
  cout << "your horse: Horse #" << horse_num << endl << endl; 
  for (int i = 0; i < horses; i++) {
      if (searchArr(horse_perf, 0, horses, sorted_dist[i]) != searchArr(horse_perf, 0, horses, sorted_dist[i - 1])) 
      {
          switch (i) {
          case 0:
              cout << "1st: Horse #"; break;
          case 1:
              cout << "2nd: Horse #"; break;
          case 2:
              cout << "3rd: Horse #"; break;
          default:
              cout << i + 1 << "th: Horse #";
          }
          int search_from;
          for (int j = i; j <= horses;j++) 
          {
              if (i == j) {
                cout << searchArr(horse_perf, 0, horses, sorted_dist[j]) + 1;
                search_from = searchArr(horse_perf, 0, horses, sorted_dist[j]) + 1;
              }
              else if (sorted_dist[j] == sorted_dist[j - 1]) {
                cout << " & #" << searchArr(horse_perf, search_from, horses, sorted_dist[j]) + 1;
                search_from = searchArr(horse_perf, search_from, horses, sorted_dist[j]) + 1;
              }
              else {
                cout << " [" << sorted_dist[i] << "]\n";
                break;
              }
          }
      }
  }
}

int main()
{
  int start_menu_input = 0;
  int difficulty = 0;
  int horse_num = 0;
  int bet_type = 0;
  float bet_amount = 0;
  float total_money = 100.0;
  char play_again;
  char menu_screen;
  int horse_perf[NUM];
  int sorted_dist[NUM];
  int horses = 0;
  int betType = 0;

  BACK_TO_MENU:
  cout << "MENU SCREEN" << endl;
  cout << "===========" << endl;
  cout << "Type in an Option (1, 2 or 3): " << endl;
  cout << endl;
  cout << "1. START " << endl;
  cout << "2. ABOUT " << endl;
  cout << "3. EXIT " << endl;
  cout << endl;
  cin >> start_menu_input;

  system("cls");
  switch (start_menu_input)
  {
    case 1: 
      do {
        display_diff_level();
        cin >> difficulty;
        system("cls");
      } while (difficulty < 1 || difficulty > 3);
          switch (difficulty) {
      case 1:
          horses = 5; break;
      case 2:
          horses = 10; break;
      case 3:
          horses = 15; break;
      }
      PLAY_AGAIN:
      do {
          cout << "Select Horse Number: " << endl;
          cout << endl;
          for (int i = 1; i <= horses; i++)
            cout << "#" << i << " - ";
          cout << endl;
          cin >> horse_num;
      } while (horse_num < 1 || horse_num > horses);
      system("cls");
      display_bet_type();
      cin >> bet_type;
      system("cls");
      input_bet(bet_amount, total_money);
      Start_Race(horse_perf, horse_num - 1, horses, difficulty);
      Copy_Arr(horse_perf, sorted_dist, 0, horses);
      sortArr(sorted_dist, 0, horses - 1);
      cout << "your goal: being top " << bet_type << endl; 
      DisplayRaceResults(horses, horse_perf, sorted_dist, horse_num);
      display_bet_result(bet_type, bet_amount, total_money, Check_Win(horse_perf, sorted_dist, betType, horse_num - 1));
      if (total_money >= 10)
      {
          cout << endl << "Feeling Lucky? Wanna Place Another Bet? (y or n)" << endl;
          cin >> play_again;
          switch (play_again)
          {
          case 'y': goto PLAY_AGAIN; break;
          case 'n': cout << "High score: $" << total_money << endl; goto BACK_TO_MENU; break;
          }
      }
      else
      {
          cout << "You do not have enough money to place another bet, Come back later ;)" << endl;
      }
      break;
    case 2:
      cout << "Welcome To Horse Racing!" << endl;
      cout << "This is a horce race betting simulator made with c++" << endl;
      cout << "where you can freely bet on horse racing without having to worry about losing real money." <<endl;
      cout << "You start off with $100 and the aim is to make as much money as you can betting on horses." <<endl;
      cout << "So, ready to test your luck? (y or n)" << endl;
      cin >> menu_screen;
      switch (menu_screen)
      {
        case 'y': goto BACK_TO_MENU; break;
        case 'n': exit(0); break;
      }
      break;
    case 3: exit(0); break;
    default: goto BACK_TO_MENU; break;
  }
  return 0;
}