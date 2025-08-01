# 🎓 Weighted Grade Calculation Program

This C program allows users to calculate final grades for students based on weighted course components. It supports both single-student and multi-student modes, and includes features such as grade calculation, class summary, student searching, and ranking.

---

## ✨ Features

- Input course components with weights and scores
- Calculate final weighted grade and letter grade (A+ to F)
- Single or multiple student modes
- Class summary: maximum, average, and median grade
- Sort students by final grade
- Search for a student by name
- Input validation and memory management included

---

## 💻 How to Compile and Run

You can run this program on any system with a C compiler, either through the terminal or a code editor like **Visual Studio Code**.

### 🔧 Requirements

- A C compiler such as **GCC** (recommended)
- (Optional) **Visual Studio Code** with the [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

### 🗂️ Steps

1. **Download the source code**:
   - Clone this repository using:
     ```bash
     git clone https://github.com/suragaafar/WeightedGradeCalculationProgram
     ```
   - Or download the `.c` file manually.

2. **Open your terminal** and navigate to the project folder:
   ```bash
   cd path/to/project
   ```
   
3. **Compile the program using GCC:**
  ```bash
  gcc suragaafar_assignment2.c -o grade_calculator -lm
  ```

4.  **Run the program:**
   ```bash
   ./grade_calculator
   ```
   
---

## 🧠 What I Learned

- How to use struct for organizing student and course data
- Recursion for grade calculations
- Dynamic memory allocation and malloc/free
- Input validation and user interaction
- Sorting, searching, and class-wide statistics in C
