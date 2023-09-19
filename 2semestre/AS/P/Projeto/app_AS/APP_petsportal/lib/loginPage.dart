import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:petsportal/homeUser.dart';

import 'homePetsitterPage.dart';

class LoginPage extends StatefulWidget {
  @override
  _LoginPageState createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  final apiUrl = 'http://10.0.2.2:5000/api/login';
  final _formKey = GlobalKey<FormState>();
  final TextEditingController _usernameController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();
  String loginMessage = '';
  bool check = false;

  Future<void> login() async {
    if (_formKey.currentState!.validate()) {
      final headers = {'Content-Type': 'application/json'};
      final body = jsonEncode({
        'username': _usernameController.text,
        'password': _passwordController.text,
      });

      final response =
          await http.post(Uri.parse(apiUrl), headers: headers, body: body);

      if (response.statusCode == 200) {
        final responseData = jsonDecode(response.body);
        print(responseData[
            'message']); //debug teste para ver se é pet_sitter ou não na consola
        if (responseData['message'] == 1) {
          check = false;
        } else {
          check = true;
        }
        setState(() {
          Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) =>
                    check ? HomePageUser() : HomePagePetSitter()),
          );
        });
      } else {
        final responseData = jsonDecode(response.body);
        final errorMessage = responseData['error'];

        setState(() {
          loginMessage = 'Login failed: $errorMessage';
        });
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Welcome back'),
        backgroundColor: Color.fromARGB(255, 94, 199, 237),
      ),
      body: Center(
        child: Padding(
          padding: EdgeInsets.all(16.0),
          child: Form(
            key: _formKey,
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                TextFormField(
                  controller: _usernameController,
                  decoration: InputDecoration(
                    labelText: 'Username',
                  ),
                  validator: (value) {
                    if (value!.isEmpty) {
                      return 'Please enter your username';
                    }
                    return null;
                  },
                ),
                SizedBox(height: 16.0),
                TextFormField(
                  controller: _passwordController,
                  obscureText: true,
                  decoration: InputDecoration(
                    labelText: 'Password',
                  ),
                  validator: (value) {
                    if (value!.isEmpty) {
                      return 'Please enter your password';
                    }
                    return null;
                  },
                ),
                SizedBox(height: 16.0),
                ElevatedButton(
                  onPressed: login,
                  child: Text('Login'),
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Color.fromARGB(255, 94, 199, 237),
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20.0),
                    ),
                    fixedSize:
                        Size(200.0, 30.0), // Set the fixed width and height
                  ),
                ),
                SizedBox(height: 16.0),
                Text(loginMessage),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
