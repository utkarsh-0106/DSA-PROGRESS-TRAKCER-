📊 DSA Progress Tracker

A C++ + MySQL project to track solved DSA problems with features like:
✔ Add, Edit, Delete problems
✔ Search and Filter problems
✔ View progress statistics
✔ Persistent storage using MySQL

🚀 Features

📝 Add Problem – Store problem details like name, platform, difficulty, and date solved.

🔍 Search Problem – Search by name or platform.

📖 View All Problems – Display every stored problem.

✏️ Edit Problem – Update problem details.

❌ Delete Problem – Remove a problem from the database.

📊 Statistics (future feature) – Track number of problems solved, grouped by difficulty/platform.

🛠️ Tech Stack

C++ (Core logic)

MySQL (Database storage)

MySQL Connector/C++ (Database connection)

⚙️ Setup Instructions
1. Clone the Repository
git clone https://github.com/<your-username>/DSA-Progress-Tracker.git
cd DSA-Progress-Tracker

2. Install MySQL Connector/C++

On macOS (Homebrew):

brew install mysql-connector-c++

3. Compile the Project
g++ main.cpp -o main \
-I/opt/homebrew/Cellar/mysql-connector-c++/9.4.0/include/ \
-L/opt/homebrew/Cellar/mysql-connector-c++/9.4.0/lib/ -lmysqlcppconnx

4. Run the Program
./main

📂 Database Setup

Run this SQL to create the database:

CREATE DATABASE dsa_tracker;
USE dsa_tracker;

CREATE TABLE problems (
    id INT AUTO_INCREMENT PRIMARY KEY,
    problem_number INT NOT NULL,
    problem_name VARCHAR(255) NOT NULL,
    platform VARCHAR(100),
    difficulty VARCHAR(50),
    personal_difficulty VARCHAR(50),
    date_solved DATE
);

🎯 Example Usage
1. Add Problem
2. View All Problems
3. Search Problem
4. Edit Problem
5. Delete Problem
6. Exit

📸 Screenshots

Add screenshots of your terminal output here (like viewing problems, searching, etc.).
Example:

🏆 Future Improvements

Add filtering by difficulty/platform

Show statistics (total solved, difficulty-wise count)

Export problems to CSV/JSON

🤝 Contributing

Pull requests are welcome! Feel free to fork and improve the project.

📜 License

This project is licensed under the MIT License.
