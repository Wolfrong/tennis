#pragma once
#include <fstream>
#include "Game.h"
#include "Game2P.h"

namespace tennis {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Menu : public Form{
	public:
		Menu(void){
			InitializeComponent();
		}
	protected:
		~Menu(){
			if (components){
				delete components;
			}
		}
	private: Button^ INFO;
		Button^ START;
		Label^ GM_SIGN;
		Button^ TWOP;
		Button^ INCREASE;
		Button^ REDUCE;
		Button^ RESULTS;
		Button^ CLEARSC;
		Button^ QUIT;
		Label^ AUTHOR;
		static void GetResults();
		System::ComponentModel::Container ^components;
		Drawing::Font^ defaultFont = gcnew Drawing::Font(L"Verdana", 10);

#pragma region Windows Form Designer generated code
		void InitializeComponent(void){
			ComponentResourceManager^ resources = gcnew ComponentResourceManager(Menu::typeid);
			INFO = gcnew Button();
			GM_SIGN = gcnew Label();
			START = gcnew Button();
			TWOP = gcnew Button();
			INCREASE = gcnew Button();
			REDUCE = gcnew Button();
			RESULTS = gcnew Button();
			CLEARSC = gcnew Button();
			QUIT = gcnew Button();
			AUTHOR = gcnew Label();
			SuspendLayout();

			INFO->Font = gcnew Drawing::Font(L"Arial Rounded MT", 15);
			GM_SIGN->Font = gcnew Drawing::Font(L"Verdana", 25, FontStyle::Bold);
			START->Font = defaultFont;
			TWOP->Font = defaultFont;
			INCREASE->Font = defaultFont;
			REDUCE->Font = defaultFont;
			RESULTS->Font = defaultFont;
			CLEARSC->Font = defaultFont;
			QUIT->Font = defaultFont;
			AUTHOR->Font = gcnew Drawing::Font(L"Verdana", 8);;

			INFO->Location = Point(1, 1);
			INFO->Size = Drawing::Size(40, 40);
			INFO->BackColor = Color::Transparent;
			INFO->Text = L"i";
			INFO->TextAlign = ContentAlignment::MiddleCenter;
			INFO->Click += gcnew EventHandler(this, &Menu::INFO_Click);

			GM_SIGN->AutoSize = true;
			GM_SIGN->Location = Point(340, 80);
			GM_SIGN->Size = Drawing::Size(120, 40);
			GM_SIGN->Text = L"Tennis";

			START->Location = Point(250, 150);
			START->Size = Drawing::Size(300, 60);
			START->Text = L"1 Player Mode";
			START->UseVisualStyleBackColor = true;
			START->Click += gcnew EventHandler(this, &Menu::START_Click);
	
			TWOP->Location = Point(250, 220);
			TWOP->Size = Drawing::Size(300, 60);
			TWOP->Text = L"2 Player Mode";
			TWOP->UseVisualStyleBackColor = true;
			TWOP->Click += gcnew EventHandler(this, &Menu::TWOP_Click);

			INCREASE->Location = Point(410, 290);
			INCREASE->Size = System::Drawing::Size(140, 60);
			INCREASE->Text = L"Increase";
			INCREASE->UseVisualStyleBackColor = true;
			INCREASE->Click += gcnew EventHandler(this, &Menu::INCREASE_Click);

			REDUCE->Location = Point(250, 290);
			REDUCE->Size = Drawing::Size(140, 60);
			REDUCE->Text = L"Reduce";
			REDUCE->UseVisualStyleBackColor = true;
			REDUCE->Click += gcnew EventHandler(this, &Menu::REDUCE_Click);

			RESULTS->Location = Point(250, 360);
			RESULTS->Size = Drawing::Size(200, 60);
			RESULTS->Text = L"Last games' results";
			RESULTS->UseVisualStyleBackColor = true;
			RESULTS->Click += gcnew EventHandler(this, &Menu::RESULTS_Click);

			CLEARSC->Location = Point(470, 360);
			CLEARSC->Size = Drawing::Size(80, 60);
			CLEARSC->Text = L"Clear Scores";
			CLEARSC->UseVisualStyleBackColor = true;
			CLEARSC->Click += gcnew EventHandler(this, &Menu::CLEARSC_Click);
	
			QUIT->Location = Point(250, 430);
			QUIT->Size = Drawing::Size(300, 60);
			QUIT->Text = L"Quit";
			QUIT->UseVisualStyleBackColor = true;
			QUIT->Click += gcnew EventHandler(this, &Menu::QUIT_Click);

			AUTHOR->AutoSize = true;
			AUTHOR->Location = Point(650, 570);
			AUTHOR->Size = Drawing::Size(100, 15);
			AUTHOR->Text = L"by Maksym Stetsiuk";

			ClientSize = Drawing::Size(800, 600);
			Controls->Add(CLEARSC);
			Controls->Add(INFO);
			Controls->Add(QUIT);
			Controls->Add(INCREASE);
			Controls->Add(REDUCE);
			Controls->Add(RESULTS);
			Controls->Add(TWOP);
			Controls->Add(AUTHOR);
			Controls->Add(GM_SIGN);
			Controls->Add(START);
			FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
			Icon = cli::safe_cast<Drawing::Icon^>(resources->GetObject(L"$this.Icon"));
			StartPosition = FormStartPosition::CenterScreen;
			Text = L"Menu";
			MaximizeBox = false;
			ResumeLayout(false);
			PerformLayout();
		}
#pragma endregion
		Void START_Click(Object^ sender, EventArgs^ e) {
			Game^ gameForm = gcnew Game();
			gameForm->Show();
			Hide();
		}
		Void TWOP_Click(Object^ sender, EventArgs^ e) {
			Game2P^ game2PForm = gcnew Game2P();
			game2PForm->Show();
			Hide();
		}
		Void INCREASE_Click(Object^ sender, EventArgs^ e) {
			Tennis::WinningScore++;
			Tennis2::WinningScore++;
			MessageBox::Show("Winning score increased to " + Tennis::WinningScore);
		}
		Void REDUCE_Click(Object^ sender, EventArgs^ e) {
			if (Tennis::WinningScore > 1 && Tennis2::WinningScore > 1) {
				Tennis2::WinningScore--;
				Tennis::WinningScore--;
				MessageBox::Show("Winning score reduced to " + Tennis::WinningScore);
			}
			else {
				MessageBox::Show("Winning score cannot be less than 1");
			}
		}
		Void RESULTS_Click(Object^ sender, EventArgs^ e) {
			GetResults();
		}
		Void CLEARSC_Click(Object^ sender, EventArgs^ e) {
			std::ofstream fout("results.txt", std::ios::trunc);
			if (!fout.is_open()) {
				MessageBox::Show("Failed to open results.txt for writing.", "Error");
				return;
			}
			fout.close();
			MessageBox::Show("Scores cleared successfully!", "Success");
		}
		Void QUIT_Click(Object ^ sender, EventArgs^ e) {
			Windows::Forms::DialogResult result = MessageBox::Show( "Are you sure you want to exit?", "Exit", 
				MessageBoxButtons::YesNo);
			if (result == Windows::Forms::DialogResult::Yes) {
				Application::Exit();
			}
		}
		Void INFO_Click(Object^ sender, EventArgs^ e) {
			MessageBox::Show(
				"This is a simple tennis game. \n\n"
				"Controls:\n"
				"1 Player Mode:\n"
				"Up Arrow (up), Down Arrow (down)\n\n"
				"Objective: Deflect the ball with your platform.\n\n"
				"2 Players Mode:\n"
				"Player 1: W (up), S (down)\n"
				"Player 2: Up Arrow (up), Down Arrow (down)\n\n"
				"Objective: Score points by hitting the ball past your opponent.\n\n"
				"Menu buttons Increase and Reduce (increase or decrease winning score)\n\n"
				"Good luck and have fun!");
		}
	};
}