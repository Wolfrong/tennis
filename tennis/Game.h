#pragma once
class Tennis {
public:
	Tennis();
	~Tennis();

	void GameOver() const;
	void UpdateGame();
	void MovePlayer(int direction);
	void SaveResults() const;

	const int PD_WIDTH = 15;
	const int PD_HEIGHT = 100;
	const int BALL_SIZE = 15;
	const int PD_SPEED = 10;
	const int UP_WALL = 50;
	const int Tick = 16;
	double BALL_SPEED = 3.0;

	static int WinningScore;
	int totalScore;
	int PlayerY;
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

	public ref class Game : public Form{
	public:
		Game(void);
	protected:
		~Game(){
			if (components){
				delete components;
			}
			if (tennis_game){
				delete tennis_game;
			}
		}
		void OnPaint(PaintEventArgs^ e) override {
			Form::OnPaint(e);
			Graphics^ g = e->Graphics;
			SolidBrush blueBrush(Color::LightGray);
			g->FillRectangle(% blueBrush, 0, 0, 800, tennis_game->UP_WALL);
		}
	private:
		System::ComponentModel::Container ^components;
		Tennis* tennis_game;
		PictureBox^ playerPlatform;
		PictureBox^ ball;
		Label^ label1;
		Label^ label2;
		Timer^ gameTimer;
		bool moveUp;
		bool moveDown;

		void OnGameTick(Object^ sender, EventArgs^ e);
		void UpdateUI();
		void OnKeyDown(Object^ sender, KeyEventArgs^ e);
		void OnKeyUp(Object^ sender, KeyEventArgs^ e);
		Drawing::Font^ defaultFont = gcnew Drawing::Font(L"Verdana", 10);

#pragma region Windows Form Designer generated code
		void InitializeComponent(void){
			components = gcnew System::ComponentModel::Container();
			label1 = gcnew Label();
			label2 = gcnew Label();
			playerPlatform = gcnew PictureBox();
			ball = gcnew PictureBox();
			label1->Font = defaultFont;
			label2->Font = defaultFont;

			label1->AutoSize = true;
			label1->Location = Point(400, 30);
			label1->BackColor = Color::Transparent;
			label1->Name = L"Score";
			label1->Size = Drawing::Size(50, 20);

			label2->AutoSize = true;
			label2->Location = Point(380, 10);
			label2->BackColor = Color::Transparent;
			label2->Name = L"Score";
			label2->Size = Drawing::Size(50, 20);
			label2->Text = L"Score";
			label2->Font = gcnew Drawing::Font(L"Arial", 12, FontStyle::Bold);

			playerPlatform->BackColor = Color::Transparent;
			playerPlatform->Size = Drawing::Size(tennis_game->PD_WIDTH, tennis_game->PD_HEIGHT);
			playerPlatform->Image = Image::FromFile("platform1.png");

			ball->BackColor = Color::Transparent;
			ball->Size = Drawing::Size(tennis_game->BALL_SIZE, tennis_game->BALL_SIZE);
			ball->Image = Image::FromFile("ball.png");

			ClientSize = Drawing::Size(800, 600);
			Controls->Add(label1);
			Controls->Add(label2);
			Controls->Add(playerPlatform);
			Controls->Add(ball);
			Text = L"Tennis";
			AutoScaleMode = Windows::Forms::AutoScaleMode::Font;
			StartPosition = FormStartPosition::CenterScreen;
			FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
			MaximizeBox = false;
			Icon = gcnew Drawing::Icon("tennis_ball.ico");
		}
#pragma endregion
	};
}