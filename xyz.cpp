#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct Question {
    string questionText;
    string options[4];
    char correctAnswer;
};
vector<Question> loadQuestions() {
    vector<Question> questions;
    ifstream file("xyz.txt");
    string line;
    
    while (getline(file, line)) {
        Question q;
        size_t pos = 0;
        string token;
        int part = 0;
        
        while ((pos = line.find("|")) != string::npos) {
            token = line.substr(0, pos);
            if (part == 0) q.questionText = token;
            else if (part >= 1 && part <= 4) q.options[part-1] = token;
            line.erase(0, pos + 1);
            part++;
        }
        q.correctAnswer = tolower(line[0]); // Ensure lowercase comparison
        questions.push_back(q);
    }
    return questions;
}

void takeQuiz(const vector<Question>& selectedQuestions) {
    int score = 0;
    char userAnswer;
for (int i = 0; i < selectedQuestions.size(); ++i) {
        cout << "\nQuestion " << i+1 << ": " << selectedQuestions[i].questionText << endl;
        for (int j = 0; j < 4; ++j) {
            cout << char('a' + j) << ") " << selectedQuestions[i].options[j] << endl;
        }
        cout << "Your answer (a/b/c/d): ";
        cin >> userAnswer;
        
        if (tolower(userAnswer) == selectedQuestions[i].correctAnswer) {
            score++;
            cout << "? Correct!\n";
        } else {
            cout << "? Wrong! Correct answer: " << selectedQuestions[i].correctAnswer << endl;
        }
    }
    cout << "\nYour score: " << score << "/10\n";
}

int main() {
    srand(time(0));
    vector<Question> allQuestions = loadQuestions();
    
   // Randomly select 10 questions
    random_shuffle(allQuestions.begin(), allQuestions.end());
    vector<Question> quizQuestions(allQuestions.begin(), allQuestions.begin() + min(10, (int)allQuestions.size()));
    
    cout << "===== QUIZ GAME =====" << endl;
    cout << "Total questions: 10\nEach correct answer: 1 point\n";
    
    takeQuiz(quizQuestions);
    return 0;
}
