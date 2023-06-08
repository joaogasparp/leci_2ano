import 'package:flutter/material.dart';
import 'loginPage.dart';
import 'signUp.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Start Page',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: StartPage(),
    );
  }
}

class StartPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: SafeArea(
          child: Column(
            children: [
              Expanded(
                flex: 1,
                child: Container(
                  color: Color.fromARGB(
                      255, 255, 255, 255), // Set your desired background color
                  child: Stack(
                    children: [
                      Align(
                        alignment: Alignment.topCenter,
                        child: Text(
                          '\n\n\n\n\n\nPets Portal',
                          style: TextStyle(
                            color: const Color.fromARGB(255, 2, 2, 2),
                            fontSize: 45.0,
                            fontWeight: FontWeight.w300,
                          ),
                        ),
                      ),
                      Positioned(
                        top: 50.0, // Set the desired top position
                        left: 100.0, // Set the desired left position
                        child: Image.asset(
                          'lib/assets/background_img.png',
                          width: 200.0, // Set the desired width
                          height: 200.0, // Set the desired height
                          fit: BoxFit
                              .contain, // Adjust the image to fit within the specified dimensions
                        ),
                      ),
                    ],
                  ),
                ),
              ),
              Expanded(
                flex: 1,
                child: Container(
                  color: Color.fromARGB(255, 254, 254, 254),
                  padding: EdgeInsets.symmetric(horizontal: 16.0),
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.start,
                    children: [
                      Expanded(child: Container()),
                      ElevatedButton(
                        onPressed: () {
                          Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => LoginPage()),
                          );
                        },
                        style: ElevatedButton.styleFrom(
                          backgroundColor: Color.fromARGB(255, 239, 239, 239),
                          shape: RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(20.0),
                          ),
                          fixedSize: Size(
                              330.0, 60.0), // Set the fixed width and height
                        ),
                        child: Text(
                          'Login                                            --->',
                          style: TextStyle(
                            fontSize: 18.0,
                            fontWeight: FontWeight.w500,
                            color: Colors.black,
                          ),
                        ),
                      ),
                      SizedBox(height: 50.0),
                      ElevatedButton(
                        onPressed: () {
                          Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => SignUpPage()),
                          );
                        },
                        style: ElevatedButton.styleFrom(
                          backgroundColor: Color.fromARGB(255, 94, 199, 237),
                          shape: RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(20.0),
                          ),
                          fixedSize: Size(
                              200.0, 30.0), // Set the fixed width and height
                        ),
                        child: Text(
                          'Sign Up',
                          style: TextStyle(
                            fontSize: 14.0,
                            fontWeight: FontWeight.w400,
                            color: const Color.fromARGB(255, 255, 255, 255),
                          ),
                        ),
                      ),
                      SizedBox(height: 100.0),
                    ],
                  ),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
























  /*
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        decoration: BoxDecoration(
          image: DecorationImage(
            image: AssetImage('lib/assets/background_img.png'),
            fit: BoxFit.cover,
            alignment: Alignment.topCenter,
          ),
        ),
        child: Center(
          child: ElevatedButton(
            onPressed: () {
              Navigator.push(
                context,
                MaterialPageRoute(builder: (context) => LoginPage()),
              );
            },
            child: Text('Go to Login'),
          ),
        ),
      ),
    );
  }
}
*/