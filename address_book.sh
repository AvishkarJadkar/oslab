#!/bin/bash

# File name where address book data will be stored
FILE="address_book.txt"

# Function to create an address book file
create_address_book() {
    touch "$FILE"
    echo "Address Book created successfully!"
}

# Function to view the contents of the address book
view_address_book() {
    if [ -s "$FILE" ]; then
        echo "Address Book Contents:"
        cat -n "$FILE"   # Display contents with line numbers
    else
        echo "Address book is empty."
    fi
}

# Function to insert a new record
insert_record() {
    echo "Enter Name:"
    read name
    echo "Enter Phone Number:"
    read phone
    echo "Enter Email Address:"
    read email

    # Append the new record to the file
    echo "$name | $phone | $email" >> "$FILE"
    echo "Record inserted successfully!"
}

# Function to delete a record by name
delete_record() {
    echo "Enter the Name of the contact to delete:"
    read name

    # Check if record exists using grep
    if grep -q "^$name" "$FILE"; then
        grep -v "^$name" "$FILE" > temp.txt   # Copy all lines except the one to delete
        mv temp.txt "$FILE"
        echo "Record deleted successfully."
    else
        echo "Record not found."
    fi
}

# Function to modify a record by name
modify_record() {
    echo "Enter the Name of the contact to modify:"
    read name

    # Check if record exists
    if grep -q "^$name" "$FILE"; then
        grep -v "^$name" "$FILE" > temp.txt   # Remove the old record

        # Get new details
        echo "Enter new Name:"
        read new_name
        echo "Enter new Phone Number:"
        read new_phone
        echo "Enter new Email Address:"
        read new_email

        # Add new record to file
        echo "$new_name | $new_phone | $new_email" >> temp.txt
        mv temp.txt "$FILE"
        echo "Record updated successfully."
    else
        echo "Record not found."
    fi
}

# ==================== MAIN MENU LOOP ====================
while true; do
    echo ""
    echo "====== Address Book Menu ======"
    echo "1) Create Address Book"
    echo "2) View Address Book"
    echo "3) Insert a Record"
    echo "4) Delete a Record"
    echo "5) Modify a Record"
    echo "0) Exit"
    echo "Choose an option (0-5):"
    read choice

    case "$choice" in
        1) create_address_book ;;
        2) view_address_book ;;
        3) insert_record ;;
        4) delete_record ;;
        5) modify_record ;;
        0) echo "Exiting program."; break ;;
        *) echo "Invalid option. Please choose 1, 2, 3, 4, 5, or 0." ;;
    esac
done

/*
1.open terminal
2.create new file- nano address_book.sh
3.paste the entire code into the nano editor
4.save and exit nano:
-Press Ctrl + O → Enter → Ctrl + X
5.Give execute permission:- chmod +x address_book.sh
6.Run the script: ./address_book.sh
7. Use the menu options (1–5 or 0) to manage your address book interactively.
*/

/*====== Address Book Menu ======
1) Create Address Book
2) View Address Book
3) Insert a Record
4) Delete a Record
5) Modify a Record
0) Exit
Choose an option (0-5): 1
Address Book created successfully!
*/