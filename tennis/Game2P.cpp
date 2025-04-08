#include "Game2P.h"
#include <fstream>
#include "Menu.h"
#include <string>

using namespace System;
using namespace System::Windows::Forms;

int Tennis2::WinningScore = 5;

Tennis2::Tennis2()
    : Player1Score(0),
	Player2Score(0),
    Player1Y(WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2),
	Player2Y(WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2),
    BallX(WINDOW_WIDTH / 2 - BALL_SIZE / 2),
    BallY(WINDOW_HEIGHT / 2 - BALL_SIZE / 2),
    BallDirX(rand() % 2 - 1),
    BallDirY(rand() % 2 - 1),
    IsGameRunning(true) {
}
Tennis2::~Tennis2() {};

void Tennis2::UpdateGame() {
    if (!IsGameRunning)
    {
        return;
    }

    BallX += BallDirX * BALL_SPEED;
     BallY += BallDirY * BALL_SPEED;

    if (BallY <= BAR_HEIGHT || BallY >= WINDOW_HEIGHT - 4 * WALL_WIDTH - BALL_SIZE) {
        BallDirY = -BallDirY;
    }

    if (Player1Score >= WinningScore || Player2Score >= WinningScore){
        IsGameRunning = false;
        return GameOver();;
    }
    if (BallX <= PADDLE_WIDTH && BallY >= Player1Y && BallY <= Player1Y + PADDLE_HEIGHT) {
        BallDirX = -BallDirX;
    }
    if (BallX >= WINDOW_WIDTH - PADDLE_WIDTH - 35 && BallY >= Player2Y && BallY <= Player2Y + PADDLE_HEIGHT) {
        BallDirX = -BallDirX;
    }
    if (BallX >= WINDOW_WIDTH -PADDLE_WIDTH)
    {
		Player1Score++;
        ResetBall();
    }
    if (BallX <= 0)
    {
		Player2Score++;
        ResetBall();
    }
}

void::Tennis2::ResetBall() {
    BallX = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
    BallY = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;
    BallDirX = -1;
	BallDirY = -1;
}

void Tennis2::MovePlayer1(int direction) {
    if (Player1Y + direction >= BAR_HEIGHT - 5 && Player1Y + direction <= WINDOW_HEIGHT - PADDLE_HEIGHT - 4 * WALL_WIDTH) {
        Player1Y += direction;
    }
}
void Tennis2::MovePlayer2(int direction) {
    if (Player2Y + direction >= BAR_HEIGHT - 5 && Player2Y + direction <= WINDOW_HEIGHT - PADDLE_HEIGHT - 4 * WALL_WIDTH) {
        Player2Y += direction;
    }
}

void Tennis2::SaveResultsToFile() {
    try {
        std::ofstream fout("results.txt", std::ios::out);
        if (!fout.is_open()) {
            throw std::ios_base::failure("Failed to open results.txt for writing.");
        }
        fout << "Score: "  << std::endl;
    }
    catch (const std::exception& e) {
        MessageBox::Show(gcnew String(e.what()), "File Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
void Tennis2::GetResultsFromFile() {
    try {
        std::ifstream fin("results.txt");
        if (!fin.is_open()) {
            throw std::ios_base::failure("Failed to open results.txt for reading.");
        }

        std::string scores;
        std::string line;
        while (std::getline(fin, line)) {
            scores += line + "\n";
        }
        fin.close();

        System::String^ managedScores = gcnew System::String(scores.c_str());
        MessageBox::Show(managedScores, "Top Scores", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    catch (const std::exception& e) {
        MessageBox::Show(gcnew String(e.what()), "File Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

void Tennis2::GameOver()
{
    SaveResultsToFile();
    IsGameRunning = false;

    if (Player1Score == WinningScore)
    {
        MessageBox::Show("Player 1 won!", "Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
	else if (Player2Score == WinningScore)
    {
        MessageBox::Show("Player 2 won!", "Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    Form^ currentForm = Form::ActiveForm;
    if (currentForm != nullptr)
    {
        currentForm->Hide();
    }

    tennis::Menu^ menuForm = gcnew tennis::Menu();
    menuForm->ShowDialog();
}