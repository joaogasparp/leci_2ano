from flask import Flask, jsonify, request
import sqlite3

app = Flask(__name__)


@app.route('/api/signup', methods=['POST'])
def signup():
    data = request.json
    username = data['username']
    password = data['password']
    is_pet_sitter = data['isPetSitter']

    save_user_to_database(username, password, is_pet_sitter)

    return jsonify({'message': 'Sign up successful'})


@app.route('/api/login', methods=['POST'])
def login():
    data = request.json
    username = data['username']
    password = data['password']
    

    user = get_user_from_database(username, password)
    

    if user:
        check = user_petsitter_check(username,password)
        return jsonify({'message': check}),200
    else:
        return jsonify({'message': 'Invalid username or password'}), 401


def save_user_to_database(username, password, is_pet_sitter):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    try:
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT,
                password TEXT,
                is_pet_sitter INTEGER
            )
        ''')

        cursor.execute('''
            INSERT INTO users (username, password, is_pet_sitter)
            VALUES (?, ?, ?)
        ''', (username, password, is_pet_sitter))

        conn.commit()
        conn.close()

        return cursor.lastrowid
    except Exception as e:
        print(f"Error saving user to database: {str(e)}")
        conn.rollback()
        conn.close()
        return None


def get_user_from_database(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute('''
        SELECT * FROM users WHERE username = ? AND password = ? 
    ''', (username, password))

    user = cursor.fetchone()
    conn.close()

    return user


def user_petsitter_check(username,password):

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    query = "SELECT is_pet_sitter FROM users WHERE username = ? AND password = ?"
    cursor.execute(query, (username,password))
    result = cursor.fetchone()

    conn.close()

    return result[0] 
    
    



if __name__ == '__main__':
    app.run()
