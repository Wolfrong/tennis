#pragma once
#include <fstream>

class Tennis {

public:
	Tennis();
	~Tennis();

	void GameOver();
	void UpdateGame();
	void MovePlayer(int direction);
	void SaveResultsToFile();
	static void GetResultsFromFile();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int PADDLE_WIDTH = 10;
	const int PADDLE_HEIGHT = 100;
	const int BALL_SIZE = 15;
	const int WALL_WIDTH = 10;
	const int BAR_HEIGHT = 4;
	const int BUTTON_WIDTH = 100;
	const int BUTTON_HEIGHT = 40;

	const int PADDLE_SPEED = 15;
	const int BALL_SPEED = 3;
	const int g_TimerDelay = 16;

	static int g_WinningScore;
	int g_totalScore;
	int g_PlayerY;
	int g_BallX;
	int g_BallY;
	int g_BallDirX;
	int g_BallDirY;
	bool IsGameRunning;

};

namespace tennis {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Game : public System::Windows::Forms::Form
	{
	public:
		Game(void)
		{
			tennis_game = new Tennis();
			InitializeComponent();


			gameTimer = gcnew Timer();
			gameTimer->Interval = tennis_game->g_TimerDelay;
			gameTimer->Tick += gcnew EventHandler(this, &Game::OnGameTick);
			gameTimer->Start();

			this->KeyDown += gcnew KeyEventHandler(this, &Game::OnKeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &Game::OnKeyUp);

			this->KeyPreview = true;
		}
	protected:
		~Game()
		{
			if (components)
			{
				delete components;
			}
			if (tennis_game)
			{
				delete tennis_game;
			}
		}

	private:
		System::ComponentModel::Container ^components;

		Tennis* tennis_game;
		PictureBox^ playerPlatform;
		PictureBox^ ball;
		Timer^ gameTimer;
		bool moveUp;
		bool moveDown;

		void OnGameTick(Object^ sender, EventArgs^ e)
		{
			if (!tennis_game->IsGameRunning)
			{
				gameTimer->Stop();
				return;
			}
			if (moveUp)
			{
				tennis_game->MovePlayer(-tennis_game->PADDLE_SPEED);
			}
			if (moveDown)
			{
				tennis_game->MovePlayer(tennis_game->PADDLE_SPEED);
			}

			tennis_game->UpdateGame();
			UpdateUI();
		}
		void UpdateUI()
		{
			this->ball->Location = System::Drawing::Point(this->tennis_game->g_BallX, this->tennis_game->g_BallY);
			this->playerPlatform->Location = System::Drawing::Point(5, this->tennis_game->g_PlayerY);
			this->label1->Text = this->tennis_game->g_totalScore.ToString();
		}
		void OnKeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Up)
			{
				moveUp = true;
			}
			else if (e->KeyCode == Keys::Down)
			{
				moveDown = true;
			}
		}

		void OnKeyUp(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Up)
			{
				moveUp = false;
			}
			else if (e->KeyCode == Keys::Down)
			{
				moveDown = false;
			}
		}
	private: System::Windows::Forms::Label^ label1;
			 System::Windows::Forms::Label^ label2;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(this->tennis_game->WINDOW_WIDTH,this->tennis_game->WINDOW_HEIGHT);
            this->Padding = System::Windows::Forms::Padding();
			this->Text = L"Tennis";
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point((this->tennis_game->WINDOW_WIDTH / 2), 50);
			this->label1->Name = L"Score";
			this->label1->Size = System::Drawing::Size(50, 20);
			this->label1->TabIndex = 1;
			this->Controls->Add(this->label1);

			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point((this->tennis_game->WINDOW_WIDTH / 2) - (this->label2->Width / 2), 30);
			this->label2->Name = L"Score";
			this->label2->Size = System::Drawing::Size(50, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Score";
			this->label2->Font = gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold);
			this->Controls->Add(this->label2);

			this->playerPlatform = gcnew PictureBox();
			this->playerPlatform->BackColor = System::Drawing::Color::Blue;
			this->playerPlatform->Size = System::Drawing::Size(this->tennis_game->PADDLE_WIDTH, this->tennis_game->PADDLE_HEIGHT);
			this->Controls->Add(this->playerPlatform);

			this->ball = gcnew PictureBox();
			this->ball->BackColor = System::Drawing::Color::Red;
			this->ball->Size = System::Drawing::Size(this->tennis_game->BALL_SIZE, this->tennis_game->BALL_SIZE);
			this->Controls->Add(this->ball);
		}
#pragma endregion
	};
}

