#pragma once
class Tennis2 {
public:
	Tennis2();
	~Tennis2();

	void GameOver() const;
	void ResetBall();
	void UpdateGame();
	void MovePlayer1(int direction);
	void MovePlayer2(int direction);
	void SaveResults() const;

	const int PD_WIDTH = 15;
	const int PD_HEIGHT = 100;
	const int BALL_SIZE = 15;
	const int BORDER_UP = 50;
	const int UP_WALL = 30;
	const int PD_SPEED = 10;
	double BALL_SPEED = 3.0;
	const int Tick = 16;

	static int WinningScore;
	int Player1Score;
	int Player2Score;
	int Player1Y;
	int Player2Y;
	double BallX;
	double BallY;
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

	public ref class Game2P : public Form
	{
	public:
		Game2P(void);
	protected:
		~Game2P(){
			if (components){
				delete components;
			}
			if (tennis_game){
				delete tennis_game;
			}
		}
		void OnPaint(PaintEventArgs^ e) override{
			Form::OnPaint(e);
			Graphics^ g = e->Graphics;
			SolidBrush blueBrush(Color::LightGray);
			g->FillRectangle(%blueBrush, 0, 0, 800, tennis_game->UP_WALL);
		}
	private:
		System::ComponentModel::Container ^components;
		Tennis2* tennis_game;
		PictureBox^ player1Platform;
		PictureBox^ player2Platform;
		PictureBox^ ball;
		Label^ label5;
		Label^ label6;
		Label^ label7;
		Timer^ gameTimer;
		bool moveUp1;
		bool moveDown1;
		bool moveUp2;
		bool moveDown2;
		void OnGameTick(Object^ sender, EventArgs^ e);
		void UpdateUI();
		void OnKeyDown(Object^ sender, KeyEventArgs^ e);
		void OnKeyUp(Object^ sender, KeyEventArgs^ e);
		Drawing::Font^ defaultFont = gcnew Drawing::Font(L"Verdana", 10);
#pragma region Windows Form Designer generated code
		void InitializeComponent(void){
			components = gcnew System::ComponentModel::Container();
			label5 = gcnew Label();
			label7 = gcnew Label();
			label6 = gcnew Label();
			player1Platform = gcnew PictureBox();
			player2Platform = gcnew PictureBox();
			ball = gcnew PictureBox();
			label5->Font = defaultFont;
			label7->Font = defaultFont;
			label6->Font = defaultFont;

			label5->AutoSize = true;
			label5->Location = Point(400 - label5->Width, 10);
			label5->BackColor = Color::Transparent;
			label5->Size = Drawing::Size(50, 20);

			label7->AutoSize = true;
			label7->Location = Point(400 + label7->Width, 10);
			label7->BackColor = Color::Transparent;
			label7->Size = Drawing::Size(50, 20);

			label6->AutoSize = true;
			label6->Location = Point(375, 10);
			label6->BackColor = Color::Transparent;
			label6->Text = L"Score";
			label6->Size = Drawing::Size(50, 30);
			label6->Font = gcnew Drawing::Font(L"Arial", 12, FontStyle::Bold);

			player1Platform->BackColor = Color::Transparent;
			player1Platform->Size = Drawing::Size(tennis_game->PD_WIDTH, tennis_game->PD_HEIGHT);
			player1Platform->Image = Image::FromFile("platform1.png");

			player2Platform->BackColor = Color::Transparent;
			player2Platform->Size = Drawing::Size(tennis_game->PD_WIDTH, tennis_game->PD_HEIGHT);
			player2Platform->Image = Image::FromFile("platform2.png");
			player2Platform->BringToFront();
			
			ball->BackColor = Color::Transparent;
			ball->Size = Drawing::Size(tennis_game->BALL_SIZE, tennis_game->BALL_SIZE);
			ball->Image = Image::FromFile("ball.png");

			ClientSize = Drawing::Size(800, 600);
			Controls->Add(label5);
			Controls->Add(label7);
			Controls->Add(label6);
			Controls->Add(player1Platform);
			Controls->Add(player2Platform);
			Controls->Add(ball);
			Text = L"Tennis2P";
			AutoScaleMode = Windows::Forms::AutoScaleMode::Font;
			StartPosition = FormStartPosition::CenterScreen;
			MaximizeBox = false;
			FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
			Icon = gcnew Drawing::Icon("tennis_ball.ico");
		}
#pragma endregion
	};
}
