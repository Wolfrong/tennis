#include "Game2P.h"
#include "Menu.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace System;
using namespace System::Windows::Forms;

int Tennis2::WinningScore = 5;

Tennis2::Tennis2()
    : Player1Score(0),
	Player2Score(0),
    Player1Y(300 - PD_HEIGHT / 2 + UP_WALL / 2),
	Player2Y(300 - PD_HEIGHT / 2 + UP_WALL / 2),
    BallX(400 - BALL_SIZE / 2 + UP_WALL / 2),
    BallY(300 - BALL_SIZE / 2 + UP_WALL / 2),
    BallDirX(rand() % 3 - 1),
    BallDirY(rand() % 3 - 1),
    IsGameRunning(true) {
    srand(time(NULL));
    if (BallDirX == 0) BallDirX = 1;
    if (BallDirY == 0) BallDirY = 1;
}
Tennis2::~Tennis2() {};

tennis::Game2P::Game2P(void) {
    tennis_game = new Tennis2();
    InitializeComponent();
    gameTimer = gcnew Timer();
    gameTimer->Interval = tennis_game->Tick;
    gameTimer->Tick += gcnew EventHandler(this, &Game2P::OnGameTick);
    gameTimer->Start();

    KeyDown += gcnew KeyEventHandler(this, &Game2P::OnKeyDown);
    KeyUp += gcnew KeyEventHandler(this, &Game2P::OnKeyUp);
    KeyPreview = true;
    this->DoubleBuffered = true;
    this->ResizeRedraw = true;
}

void tennis::Game2P::OnGameTick(Object^ sender, EventArgs^ e) {
    if (!tennis_game->IsGameRunning) {
        gameTimer->Stop();
        return;
    }
    if (moveUp1) {
        tennis_game->MovePlayer1(-tennis_game->PD_SPEED);
    }
    if (moveDown1) {
        tennis_game->MovePlayer1(tennis_game->PD_SPEED);
    }
    if (moveUp2) {
        tennis_game->MovePlayer2(-tennis_game->PD_SPEED);
    }
    if (moveDown2) {
        tennis_game->MovePlayer2(tennis_game->PD_SPEED);
    }
    tennis_game->UpdateGame();
    UpdateUI();
}
void tennis::Game2P::UpdateUI() {
    ball->Location = Point((int)tennis_game->BallX, (int)tennis_game->BallY);
    player1Platform->Location = Point(5, tennis_game->Player1Y);
    player2Platform->Location = Point(780, tennis_game->Player2Y);
    label5->Text = ((int)tennis_game->Player1Score).ToString();
    label7->Text = ((int)tennis_game->Player2Score).ToString();
}
void tennis::Game2P::OnKeyDown(Object^ sender, KeyEventArgs^ e) {
    if (e->KeyCode == Keys::Up) {
        moveUp2 = true;
    }
    else if (e->KeyCode == Keys::Down) {
        moveDown2 = true;
    }
    if (e->KeyCode == Keys::W) {
        moveUp1 = true;
    }
    else if (e->KeyCode == Keys::S) {
        moveDown1 = true;
    }
}
void tennis::Game2P::OnKeyUp(Object^ sender, KeyEventArgs^ e) {
    if (e->KeyCode == Keys::Up) {
        moveUp2 = false;
    }
    else if (e->KeyCode == Keys::Down) {
        moveDown2 = false;
    }
    else if (e->KeyCode == Keys::W) {
        moveUp1 = false;
    }
    else if (e->KeyCode == Keys::S) {
        moveDown1 = false;
    }
}

void Tennis2::UpdateGame() {
    if (!IsGameRunning){
        return;
    }

    if (Player1Score >= WinningScore || Player2Score >= WinningScore) {
        IsGameRunning = false;
        return GameOver();
    }

    BallX += BallDirX * BALL_SPEED;
	BallY += BallDirY * BALL_SPEED;

    if (BallY <= UP_WALL || BallY >= 600 - BALL_SIZE) {
        BallDirY = -BallDirY;
    }
		
    if (BallX <= PD_WIDTH + 5 && BallY >= Player1Y && BallY <= Player1Y + PD_HEIGHT) {
        BallDirX = -BallDirX;
        if (BALL_SPEED < 15) {
            BALL_SPEED += 0.2;
        }
    }
    if (BallX >= 800 - PD_WIDTH - BALL_SIZE - 5 && BallY >= Player2Y && BallY <= Player2Y + PD_HEIGHT) {
        BallDirX = -BallDirX;
        if (BALL_SPEED < 15) {
            BALL_SPEED += 0.2;
        }
    }
    if (BallX >= 800){
		Player1Score++;
        ResetBall();
    }
    if (BallX <= 0){
		Player2Score++;
        ResetBall();
    }
}
void Tennis2::ResetBall() {
    BallX = 400 - BALL_SIZE / 2 - UP_WALL;
    BallY = 300 - BALL_SIZE / 2 - UP_WALL;
    BALL_SPEED = 5.0;
    BallDirX = rand() % 3 - 1;
	BallDirY = rand() % 3 - 1;
    if (!BallDirX) BallDirX = 1;
	if (!BallDirY) BallDirY = 1;
}
void Tennis2::MovePlayer1(int direction) {
    if (Player1Y + direction >= UP_WALL && Player1Y + direction <= 600 - PD_HEIGHT) {
        Player1Y += direction;
    }
}
void Tennis2::MovePlayer2(int direction) {
    if (Player2Y + direction >= UP_WALL && Player2Y + direction <= 600 - PD_HEIGHT) {
        Player2Y += direction;
    }
}
void Tennis2::SaveResults() const{
    const int maxResults = 5;
    std::string results[maxResults];
    int count = 0;

    std::ifstream fin("results.txt");
    while (fin && count < maxResults) {
        std::getline(fin, results[count]);
        if (!results[count].empty()) {
            count++;
        }
    }
    fin.close();

    if (count == maxResults) {
        for (int i = 1; i < maxResults; i++) {
            results[i - 1] = results[i];
        }
        count--;
    }

    results[count] = "Score P1: " + std::to_string(Player1Score) + " Score P2: " + std::to_string(Player2Score);
    count++;

    std::ofstream fout("results.txt", std::ios::trunc);
    for (int i = 0; i < count; i++) {
        fout << results[i] << std::endl;
    }
    fout.close();
}
void Tennis2::GameOver() const{
    SaveResults();
    if (Player1Score == WinningScore){
        MessageBox::Show("Player 1 won!", "Game Over");
    }
	else if (Player2Score == WinningScore){
        MessageBox::Show("Player 2 won!", "Game Over");
    }
    Form^ currentForm = Form::ActiveForm;
    if (currentForm) {
        currentForm->Hide();
    }
    tennis::Menu^ menuForm = gcnew tennis::Menu();
    menuForm->ShowDialog();
}