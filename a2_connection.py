
!pip install mysql-connector-python

import mysql.connector

import mysql.connector

def get_connection():
    return mysql.connector.connect(
        host="localhost",
        user="DEO",
        password="abc",
        database="DBMS"
    )



def insert_student(id, name, age):
    db = get_connection()
    cursor = db.cursor()
    query = "INSERT INTO students (id, name, age) VALUES (%s, %s, %s)"
    cursor.execute(query, (id, name, age))
    db.commit()
    print("Record inserted!")
    cursor.close()
    db.close()


def update_student(id, new_name, new_age):
    db = get_connection()
    cursor = db.cursor()
    query = "UPDATE students SET name=%s, age=%s WHERE id=%s"
    cursor.execute(query, (new_name, new_age, id))
    db.commit()
    print("Record updated!")
    cursor.close()
    db.close()



def delete_student(id):
    db = get_connection()
    cursor = db.cursor()
    query = "DELETE FROM students WHERE id=%s"
    cursor.execute(query, (id,))
    db.commit()
    print("Record deleted!")
    cursor.close()
    db.close()


while True:
    print("\n-------- MENU --------")
    print("1. Insert Student")
    print("2. Update Student")
    print("3. Delete Student")
    print("4. Exit")

    choice = int(input("Enter choice: "))

    if choice == 1:
        id = int(input("Enter ID: "))
        name = input("Enter Name: ")
        age = int(input("Enter Age: "))
        insert_student(id, name, age)

    elif choice == 2:
        id = int(input("Enter ID to Update: "))
        name = input("Enter New Name: ")
        age = int(input("Enter New Age: "))
        update_student(id, name, age)

    elif choice == 3:
        id = int(input("Enter ID to Delete: "))
        delete_student(id)

    elif choice == 4:
        print("Exiting...")
        break

    else:
        print("Invalid choice!")
