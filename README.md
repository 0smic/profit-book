# Profit Book

Profit Book is a simple command-line tool to track daily income, expenses, and profits. It allows you to add daily financial details, view a list of past entries, and check the total profit or loss over time.

## Features

- Add daily financial details, including income, expenses, and profit/loss of restaurants etc
- View a list of all past entries.
- Check the total profit or loss accumulated over time.
- Command-line interface for easy interaction.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- Windows or Linux operating system

### Build and Run

1. Clone the repository:

   ```bash
   git clone https://github.com/0smic/profit-book.git

2. Navigate to the project directory:
   ```bash
   cd profit-book/src

3. Compile the Code
   ```bash
   gcc -o profit_book profit_book.c
4. Run the executable:
     Execute the profit book normally like you do for others

### Usage

- Choose between taking new information or adding new information.
- Use the command-line interface to view a list of entries, check total profit, or exit the program.

### Commands

- list     : View basic details of each recorded day.
- total    : View the total profit or loss over all recorded days.
- highest  : View the day with the highest profit.
- lowest   : View the day with the lowest profit.
- elaborate: View detailed information for each recorded day.
- search   : Search for specific day details based on month, date, or both.
- help     : Display a list of available commands
