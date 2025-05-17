#include "Game.h"
#include "Menu.h"
#include <fstream>
#include <string>

using namespace System;
using namespace System::Windows::Forms;

int Tennis::WinningScore = 5;

Tennis::Tennis()
    : totalScore(0),
    PlayerY(300 - PD_HEIGHT / 2 + UP_WALL / 2),
    BallX(400 - BALL_SIZE / 2 + UP_WALL / 2),
    BallY(300 - BALL_SIZE / 2 + UP_WALL / 2),
    BallDirX(rand() % 3 - 1),
    BallDirY(rand() % 3 - 1),
	IsGameRunning(true){
    srand(time(NULL));
	if (BallDirX == 0) BallDirX = 1;
	if (BallDirY == 0) BallDirY = 1;
}
Tennis::~Tennis() {};

tennis::Game::Game(void) {
	tennis_game = new Tennis();
	InitializeComponent();
	gameTimer = gcnew Timer();
	gameTimer->Interval = tennis_game->Tick;
	gameTimer->Tick += gcnew EventHandler(this, &Game::OnGameTick);
	gameTimer->Start();
	KeyDown += gcnew KeyEventHandler(this, &Game::OnKeyDown);
	KeyUp += gcnew KeyEventHandler(this, &Game::OnKeyUp);
	KeyPreview = true;
    this->DoubleBuffered = true;
    this->ResizeRedraw = true;
}

void tennis::Game::OnGameTick(Object^ sender, EventArgs^ e) {
    if (!tennis_game->IsGameRunning) {
        gameTimer->Stop();
        return;
    }
    if (moveUp) {
        tennis_game->MovePlayer(-tennis_game->PD_SPEED);
    }
    if (moveDown) {
        tennis_game->MovePlayer(tennis_game->PD_SPEED);
    }
    tennis_game->UpdateGame();
    UpdateUI();
}
void tennis::Game::UpdateUI() {
	ball->Location = Point((int)tennis_game->BallX, (int)tennis_game->BallY);
	playerPlatform->Location = Point(5, tennis_game->PlayerY);
	label1->Text = tennis_game->totalScore.ToString();
}
void tennis::Game::OnKeyDown(Object^ sender, KeyEventArgs^ e) {
    if (e->KeyCode == Keys::Up) {
        moveUp = true;
    }
    else if (e->KeyCode == Keys::Down) {
        moveDown = true;
    }
}
void tennis::Game::OnKeyUp(Object^ sender, KeyEventArgs^ e) {
    if (e->KeyCode == Keys::Up) {
        moveUp = false;
    }
    else if (e->KeyCode == Keys::Down) {
        moveDown = false;
    }
}

void Tennis::UpdateGame() {
    if(!IsGameRunning){
        return;
    }
    if (totalScore >= WinningScore || BallX <= 0) {
        IsGameRunning = false;
        return GameOver();;
    }

    BallX += BallDirX * BALL_SPEED;
    BallY += BallDirY * BALL_SPEED;

    if (BallY <= UP_WALL || BallY >= 600 - BALL_SIZE){
        BallDirY = -BallDirY;
    }
    if (BallX >= 800 - BALL_SIZE) {
        BallDirX = -BallDirX;
    }
    if (BallX <= PD_WIDTH + 5 && BallY >= PlayerY && BallY <= PlayerY + PD_HEIGHT) {
        BallDirX = -BallDirX;
        totalScore++;
        if(BALL_SPEED < 15) {
            BALL_SPEED += 0.3;
        }
    }
}
void Tennis::MovePlayer(int direction) {
    if (PlayerY + direction >= UP_WALL && PlayerY + direction <= 600 - PD_HEIGHT) {
        PlayerY += direction;
    }
}
void Tennis::SaveResults() const{
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

    results[count] = "Score: " + std::to_string(totalScore);
    count++;

    std::ofstream fout("results.txt", std::ios::trunc);
    for (int i = 0; i < count; i++) {
        fout << results[i] << std::endl;
    }
    fout.close();
}
void Tennis::GameOver() const{
    SaveResults();
    if (totalScore < WinningScore){
        MessageBox::Show("You lost!", "Game Over");
    }
    else{
        MessageBox::Show("You won!", "Game Over");
    }
    Form^ currentForm = Form::ActiveForm;
    if (currentForm){
        currentForm->Hide();
    }
    tennis::Menu^ menuForm = gcnew tennis::Menu();
    menuForm->ShowDialog();
}