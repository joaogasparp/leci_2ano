import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:petsportal/homePetsitterPage.dart';
import 'package:petsportal/homeUser.dart';

class SignUpPage extends StatefulWidget {
  @override
  _SignUpPageState createState() => _SignUpPageState();
}

class _SignUpPageState extends State<SignUpPage> {
  final apiUrl = 'http://10.0.2.2:5000/api/signup';
  final _formKey = GlobalKey<FormState>();
  final TextEditingController _usernameController = TextEditingController();
  final TextEditingController _idPassportController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();
  String signUpMessage = '';
  bool isPetSitter = false;

  Future<void> signUp() async {
    if (_formKey.currentState!.validate()) {
      final headers = {'Content-Type': 'application/json'};
      final body = jsonEncode({
        'username': _usernameController.text,
        'idPassport': _idPassportController.text,
        'password': _passwordController.text,
        'isPetSitter': isPetSitter,
      });

      final response =
          await http.post(Uri.parse(apiUrl), headers: headers, body: body);

      if (response.statusCode == 200) {
        setState(() {
          Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) =>
                    isPetSitter ? HomePagePetSitter() : HomePageUser()),
          );
        });
      } else {
        setState(() {
          signUpMessage = 'Sign up failed';
        });
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
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
                  controller: _idPassportController,
                  decoration: InputDecoration(
                    labelText: 'ID/Passport',
                  ),
                  validator: (value) {
                    if (value!.isEmpty) {
                      return 'Please enter your ID/Passport';
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
                      return 'Please enter a password';
                    }
                    return null;
                  },
                ),
                SizedBox(height: 16.0),
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Text('Are you a pet sitter?'),
                    Checkbox(
                      value: isPetSitter,
                      onChanged: (value) {
                        setState(() {
                          isPetSitter = value!;
                        });
                      },
                    ),
                  ],
                ),
                SizedBox(height: 16.0),
                ElevatedButton(
                  onPressed: signUp,
                  child: Text('Sign Up'),
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Color.fromARGB(255, 94, 199, 237),
                  ),
                ),
                SizedBox(height: 16.0),
                Text(
                  signUpMessage,
                  style: TextStyle(color: Colors.red),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
