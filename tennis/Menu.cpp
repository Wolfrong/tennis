#include "Menu.h"
#include <string>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

void tennis::Menu::GetResults() {
        std::ifstream fin("results.txt");
        if (!fin.is_open()) {
            throw std::ios_base::failure("Failed to open results.txt for reading.");
        }
		if (fin.peek() == std::ifstream::traits_type::eof()){
			MessageBox::Show("No results found.", "Results");
			fin.close();
			return;
		}
        std::string scores;
        std::string line;
        while (std::getline(fin, line)) {
            scores += line + "\n";
        }
        fin.close();
        System::String^ managedScores = gcnew System::String(scores.c_str());
        MessageBox::Show(managedScores, "Scores");
}

[STAThread]
int main(array<String^>^ args) {
    srand(time(0));
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    tennis::Menu form;
    Application::Run(% form);
    return 0;
}
