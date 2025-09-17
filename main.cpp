#include <iostream>
#include <string>
#include <limits>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;


void addProblem(Session &sess, Schema &db, int problem_number, std::string problem_name, std::string platform,
                std::string difficulty, std::string personal_difficulty, std::string date_solved) {
    try {
        Table problemsTable = db.getTable("problems");
        problemsTable.insert("problem_number", "problem_name", "platform", "difficulty", "personal_difficulty", "date_solved")
                     .values(problem_number, problem_name, platform, difficulty, personal_difficulty, date_solved)
                     .execute();
        cout << "Problem added successfully!" << endl;
    }
    catch (const mysqlx::Error &err) {
        cerr << "Error inserting problem: " << err.what() << endl;
    }
}
void viewAllProblems(Schema &db) {
    try {
        Table problemsTable = db.getTable("problems");

        RowResult result = problemsTable.select("*").execute();

        for (Row row : result) {
            cout << "ID: " << row[0] 
                 << ", Number: " << row[1]
                 << ", Name: " << row[2]
                 << ", Platform: " << row[3]
                 << ", Difficulty: " << row[4]
                 << ", Personal Difficulty: " << row[5]
                 << ", Date Solved: ";

            Value date_val = row[6];
            if (date_val.isNull()) {
                cout << "NULL";
            } else {
                try {
                    cout << date_val.get<std::string>(); // Try to extract as string
                } catch (const std::exception &ex) {
                    cout << "Error reading date: " << ex.what();
                }
            }
            cout << endl;
        }
    }
    catch (const mysqlx::Error &err) {
        cerr << "Error fetching problems: " << err.what() << endl;
    }
}
void searchProblem(Schema &db, const std::string &keyword) {
    try {
        Table problemsTable = db.getTable("problems");

        RowResult result = problemsTable.select("*")
            .where("problem_name LIKE :kw OR platform LIKE :kw")
            .bind("kw", "%" + keyword + "%")
            .execute();

        if (result.count() == 0) {
            cout << "No matching problems found for keyword: " << keyword << endl;
            return;
        }

        cout << "Matching problems for keyword: " << keyword << endl;

        for (Row row : result) {
            cout << "ID: " << row[0] 
                 << ", Number: " << row[1]
                 << ", Name: " << row[2]
                 << ", Platform: " << row[3]
                 << ", Difficulty: " << row[4]
                 << ", Personal Difficulty: " << row[5]
                 << ", Date Solved: ";

            Value date_val = row[6];
            if (date_val.isNull()) {
                cout << "NULL";
            } else {
                try {
                    cout << date_val.get<std::string>(); // Try to extract as string
                } catch (const std::exception &ex) {
                    cout << "Error reading date: " << ex.what();
                }
            }
            cout << endl;
        }
    }
    catch (const mysqlx::Error &err) {
        cerr << "Error searching problems: " << err.what() << endl;
    }
}

void editProblem(Schema &db) {
    try {
        Table problemsTable = db.getTable("problems");

        int problem_number;
        cout << "Enter the problem number of the problem you want to edit: ";
        cin >> problem_number;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer

        std::string problem_name, platform, difficulty, personal_difficulty, date_solved;

        cout << "Enter new problem name: ";
        std::getline(std::cin, problem_name);

        cout << "Enter new platform: ";
        std::getline(std::cin, platform);

        cout << "Enter new difficulty: ";
        std::getline(std::cin, difficulty);

        cout << "Enter new personal difficulty: ";
        std::getline(std::cin, personal_difficulty);

        cout << "Enter new date solved (YYYY-MM-DD): ";
        std::getline(std::cin, date_solved);

        // Perform the update
        problemsTable.update()
            .set("problem_name", problem_name)
            .set("platform", platform)
            .set("difficulty", difficulty)
            .set("personal_difficulty", personal_difficulty)
            .set("date_solved", date_solved)
            .where("problem_number = :num")
            .bind("num", problem_number)
            .execute();

        cout << "Problem updated successfully!" << endl;

    } catch (const mysqlx::Error &err) {
        cerr << "Error editing problem: " << err.what() << endl;
    }
}

void deleteProblem(Schema &db) {
    try {
        Table problemsTable = db.getTable("problems");
        int problem_number;
        std::cout << "Enter the problem number to delete: ";
        std::cin >> problem_number;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        problemsTable.remove()
            .where("problem_number = :num")
            .bind("num", problem_number)
            .execute();

        std::cout << "Problem deleted successfully!" << std::endl;
    } catch (const mysqlx::Error &err) {
        std::cerr << "Error deleting problem: " << err.what() << std::endl;
    }
}

int main() {
    try {
        Session sess("localhost", 33060, "root", "Test@0106");
        Schema db = sess.getSchema("dsa_tracker");

        int choice;
do {
    std::cout << "\n1. Add Problem\n"
              << "2. View All Problems\n"
              << "3. Search Problem\n"
              << "4. Edit Problem\n"
              << "5. Delete Problem\n"
              << "6. Exit\n"
              << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush newline

    switch(choice) {
        case 1: { 
            int problem_number;
            std::string problem_name, platform, difficulty, personal_difficulty, date_solved;

            std::cout << "Enter problem number: ";
            std::cin >> problem_number;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Enter problem name: ";
            std::getline(std::cin, problem_name);

            std::cout << "Enter platform: ";
            std::getline(std::cin, platform);

            std::cout << "Enter difficulty: ";
            std::getline(std::cin, difficulty);

            std::cout << "Enter personal difficulty: ";
            std::getline(std::cin, personal_difficulty);

            std::cout << "Enter date solved (YYYY-MM-DD): ";
            std::getline(std::cin, date_solved);

            addProblem(sess, db, problem_number, problem_name, platform, difficulty, personal_difficulty, date_solved);
            break;
        }

        case 2: 
            viewAllProblems(db);
            break;

        case 3: {
            std::string keyword;
            std::cout << "Enter keyword to search: ";
            std::getline(std::cin, keyword);
            searchProblem(db, keyword);
            break;
        }

        case 4: 
            editProblem(db);
            break;

        case 5: 
            deleteProblem(db);
            break;

        case 6: 
            std::cout << "Exiting...\n"; 
            break;

        default: 
            std::cout << "Invalid choice!\n"; 
            break;
    }

    } while(choice != 6);

        sess.close();
    } catch (const mysqlx::Error &err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 1;
    }
    return 0;
}
