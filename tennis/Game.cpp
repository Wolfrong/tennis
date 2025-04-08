#include "Game.h"
#include <fstream>
#include "Menu.h"
#include <string>

using namespace System;
using namespace System::Windows::Forms;

int Tennis::g_WinningScore = 5;

Tennis::Tennis()
    : g_totalScore(0),
    g_PlayerY(WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2),
    g_BallX(WINDOW_WIDTH / 2 - BALL_SIZE / 2),
    g_BallY(WINDOW_HEIGHT / 2 - BALL_SIZE / 2),
    g_BallDirX(rand() % 2 - 1),
    g_BallDirY(rand() % 2 - 1),
	IsGameRunning(true){
}
Tennis::~Tennis() {};

void Tennis::UpdateGame() {
    if(!IsGameRunning)
    {
        return;
    }

    g_BallX += g_BallDirX * BALL_SPEED;
    g_BallY += g_BallDirY * BALL_SPEED;

    if (g_BallY <= BAR_HEIGHT || g_BallY >= WINDOW_HEIGHT - 4 * WALL_WIDTH - BALL_SIZE){
        g_BallDirY = -g_BallDirY;
    }
    if (g_BallX >= WINDOW_WIDTH - 2 * WALL_WIDTH - BALL_SIZE) {
        g_BallDirX = -g_BallDirX;
    }

    if (g_totalScore >= g_WinningScore) {
		IsGameRunning = false;
        return GameOver();;
    }
    if (g_BallX <= 0) {
		IsGameRunning = false;
        return GameOver();
    }
    if (g_BallX <= PADDLE_WIDTH && g_BallY >= g_PlayerY && g_BallY <= g_PlayerY + PADDLE_HEIGHT ) {
        g_BallDirX = -g_BallDirX;
        g_totalScore++;
    }
}

void Tennis::MovePlayer(int direction) {
    if (g_PlayerY + direction >= BAR_HEIGHT - 5 && g_PlayerY + direction <= WINDOW_HEIGHT - PADDLE_HEIGHT - 4 * WALL_WIDTH) {
        g_PlayerY += direction;
    }
}

void Tennis::SaveResultsToFile() {
    try {
        std::ofstream fout("results.txt", std::ios::out | std::ios::trunc);
        if (!fout.is_open()) {
            throw std::ios_base::failure("Failed to open results.txt for writing.");
        }
        fout << "Score: " << g_totalScore << std::endl;
    }
    catch (const std::exception& e) {
        MessageBox::Show(gcnew String(e.what()), "File Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
	void Tennis::GetResultsFromFile() {
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
void Tennis::GameOver()
{
    SaveResultsToFile();
	IsGameRunning = false;

    if (g_totalScore < g_WinningScore)
    {
        MessageBox::Show("You lost!", "Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    else
    {
        MessageBox::Show("You won!", "Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    Form^ currentForm = Form::ActiveForm;
    if (currentForm != nullptr)
    {
        currentForm->Hide();
    }

    tennis::Menu^ menuForm = gcnew tennis::Menu();
    menuForm->ShowDialog();
}

[STAThread]
int main(array<String^>^ args)
{
    srand(time(NULL));
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    tennis::Menu form;
    Application::Run(% form);

    return 0;
}