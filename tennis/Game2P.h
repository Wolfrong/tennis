#pragma once

class Tennis2 {

public:
	Tennis2();
	~Tennis2();

	void GameOver();
	void ResetBall();
	void UpdateGame();
	void MovePlayer1(int direction);
	void MovePlayer2(int direction);
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
	const int TimerDelay = 16;

	static int WinningScore;
	int Player1Score;
	int Player2Score;
	int Player1Y;
	int Player2Y;
	int BallX;
	int BallY;
	int BallDirX;
	int BallDirY;
	bool IsGameRunning;

};
namespace tennis {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Game2P : public System::Windows::Forms::Form
	{
	public:
		Game2P(void)
		{
			tennis_game = new Tennis2();
			InitializeComponent();


			gameTimer = gcnew Timer();
			gameTimer->Interval = tennis_game->TimerDelay;
			gameTimer->Tick += gcnew EventHandler(this, &Game2P::OnGameTick);
			gameTimer->Start();

			this->KeyDown += gcnew KeyEventHandler(this, &Game2P::OnKeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &Game2P::OnKeyUp);

			this->KeyPreview = true;
		}

	protected:
		~Game2P()
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

		Tennis2* tennis_game;
		PictureBox^ player1Platform;
		PictureBox^ player2Platform;
		PictureBox^ ball;
		Timer^ gameTimer;
		bool moveUp1;
		bool moveDown1;
		bool moveUp2;
		bool moveDown2;

		void OnGameTick(Object^ sender, EventArgs^ e)
		{
			if (!tennis_game->IsGameRunning)
			{
				gameTimer->Stop();
				return;
			}
			if (moveUp1)
			{
				tennis_game->MovePlayer1(-tennis_game->PADDLE_SPEED);
			}
			if (moveDown1)
			{
				tennis_game->MovePlayer1(tennis_game->PADDLE_SPEED);
			}
			if (moveUp2)
			{
				tennis_game->MovePlayer2(-tennis_game->PADDLE_SPEED);
			}
			if (moveDown2)
			{
				tennis_game->MovePlayer2(tennis_game->PADDLE_SPEED);
			}

			tennis_game->UpdateGame();
			UpdateUI();
		}
		void UpdateUI()
		{
			this->ball->Location = System::Drawing::Point(this->tennis_game->BallX, this->tennis_game->BallY);
			this->player1Platform->Location = System::Drawing::Point(5, this->tennis_game->Player1Y);
			this->player2Platform->Location = System::Drawing::Point(770, this->tennis_game->Player2Y);
			this->label5->Text = this->tennis_game->Player1Score.ToString();
			this->label7->Text = this->tennis_game->Player2Score.ToString();
		}
		void OnKeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Up)
			{
				moveUp2 = true;
			}
			else if (e->KeyCode == Keys::Down)
			{
				moveDown2 = true;
			}
			else if (e->KeyCode == Keys::W)
			{
				moveUp1 = true;
			}
			else if (e->KeyCode == Keys::S)
			{
				moveDown1 = true;
			}
		}

		void OnKeyUp(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Up)
			{
				moveUp2 = false;
			}
			else if (e->KeyCode == Keys::Down)
			{
				moveDown2 = false;
			}
			else if (e->KeyCode == Keys::W)
			{
				moveUp1 = false;
			}
			else if (e->KeyCode == Keys::S)
			{
				moveDown1 = false;
			}
		}
	private: System::Windows::Forms::Label^ label5;
		   System::Windows::Forms::Label^ label6;
		   System::Windows::Forms::Label^ label7;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(this->tennis_game->WINDOW_WIDTH, this->tennis_game->WINDOW_HEIGHT);
			this->Padding = System::Windows::Forms::Padding();
			this->Text = L"Tennis2P";
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(this->tennis_game->WINDOW_WIDTH / 2 - 1.5 * this->label5->Width, 20);
			this->label5->Name = L"Score";
			this->label5->Size = System::Drawing::Size(50, 20);
			this->label5->TabIndex = 1;
			this->Controls->Add(this->label5);

			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(this->tennis_game->WINDOW_WIDTH / 2 + this->label7->Width, 20);
			this->label7->Name = L"Score";
			this->label7->Size = System::Drawing::Size(50, 20);
			this->label7->TabIndex = 1;
			this->Controls->Add(this->label7);

			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point((this->tennis_game->WINDOW_WIDTH / 2) - (this->label6->Width / 2), 0);
			this->label6->Name = L"Score";
			this->label6->Size = System::Drawing::Size(50, 30);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Score:";
			this->label6->Font = gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold);
			this->Controls->Add(this->label6);

			this->player1Platform = gcnew PictureBox();
			this->player1Platform->BackColor = System::Drawing::Color::Blue;
			this->player1Platform->Size = System::Drawing::Size(this->tennis_game->PADDLE_WIDTH, this->tennis_game->PADDLE_HEIGHT);
			this->Controls->Add(this->player1Platform);

			this->player2Platform = gcnew PictureBox();
			this->player2Platform->BackColor = System::Drawing::Color::Red;
			this->player2Platform->Size = System::Drawing::Size(this->tennis_game->PADDLE_WIDTH, this->tennis_game->PADDLE_HEIGHT);
			this->player2Platform->BringToFront();
			this->Controls->Add(this->player2Platform);

			this->ball = gcnew PictureBox();
			this->ball->BackColor = System::Drawing::Color::Black;
			this->ball->Size = System::Drawing::Size(this->tennis_game->BALL_SIZE, this->tennis_game->BALL_SIZE);
			this->Controls->Add(this->ball);
		}
#pragma endregion
	};
}
