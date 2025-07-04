
from flask import Flask, jsonify, request

app = Flask(__name__)

users_data = [
    {'id' : 1, 'name': 'John Doe', 'email': 'john@example.com'},
    {'id' : 2, 'name': 'Jane Smith', 'email': 'jane@example.com'}
]

@app.route('/api/users/', methods=['GET'])
def get_users():
    return jsonify({
        'users': users_data,
        'count': len(users_data)
    })

@app.route('/api/users/<int:user_id>', methods=['GET'])
def get_user(user_id):
    user = next((user for user in users_data if user['id'] == user_id), None)
    if user:
        return jsonify(user)
    else:
        return jsonify({'error': 'User not found'}), 404


@app.route('/api/users/', methods=['POST'])
def create_user():
    data = request.get_json()
    if not data or 'name' not in data or 'email' not in data:
        return jsonify({'error': 'Invalid request data'}), 400
    
    new_user = {
        'id': len(users_data) + 1,
        'name': data['name'],
        'email': data['email']
    }
    users_data.append(new_user)
    return jsonify(new_user), 201

@app.route('/api/users/<int:user_id>', methods=['PUT'])
def update_user(user_id):
    data = request.get_json()
    user = next((user for user in users_data if user['id'] == user_id), None)
    if user:
        user['name'] = data.get('name', user['name'])
        user['email'] = data.get('email', user['email'])
        return jsonify(user)
    else:
        return jsonify({'error': 'User not found'}), 404



if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5100, debug=True)


