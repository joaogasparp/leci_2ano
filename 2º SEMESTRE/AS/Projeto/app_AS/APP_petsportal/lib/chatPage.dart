import 'package:flutter/material.dart';
import 'package:petsportal/profileUserPage.dart';
import 'callPetsitterPage.dart';
import 'chatMaria.dart';
import 'homeUser.dart';

class ChatPage extends StatefulWidget {
  @override
  _ChatPageState createState() => _ChatPageState();
}

class _ChatPageState extends State<ChatPage> {
  final List<User> users = [
    User(
      name: 'Maria',
      lastMessage: 'Olá, como está?',
      time: '10:30',
      imagePath: 'assets/maria.jpg',
    ),
    User(
      name: 'João',
      lastMessage: 'Até uma próxima. :)',
      time: '21:45',
      imagePath: 'assets/jonh.png',
    ),
    User(
      name: 'Helena',
      lastMessage: 'Obrigado!',
      time: 'Ontem',
      imagePath: 'assets/emily.jpg',
    ),
  ];

  int _selectedIndex = 1;

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
    if (_selectedIndex == 0) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => HomePageUser()),
      );
    }
    if (_selectedIndex == 1) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => ChatPage()),
      );
    }
    if (_selectedIndex == 2) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => callPetsitterPage()),
      );
    }
    if (_selectedIndex == 3) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => profileUser()),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        automaticallyImplyLeading: false, // Remove the back button
        title: const Text(
          'Messages',
          style: TextStyle(
            fontWeight: FontWeight.bold,
            fontSize: 20.0,
          ),
        ),
        backgroundColor: Color.fromRGBO(255, 152, 84, 1),
        elevation: 0,
      ),
      body: Container(
        color: Color(0xFFEDEDED),
        child: ListView.builder(
          padding: EdgeInsets.symmetric(vertical: 10.0),
          itemCount: users.length,
          itemBuilder: (context, index) {
            final user = users[index];
            return Padding(
              padding:
                  const EdgeInsets.symmetric(vertical: 8.0, horizontal: 16.0),
              child: Container(
                decoration: BoxDecoration(
                  border: Border.all(
                    color: Colors.grey.withOpacity(0.5),
                    width: 1.0,
                  ),
                  borderRadius: BorderRadius.circular(10.0),
                ),
                child: Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: ListTile(
                    leading: CircleAvatar(
                      backgroundImage: AssetImage(user.imagePath),
                    ),
                    title: Text(
                      user.name,
                      style: const TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 16.0,
                      ),
                    ),
                    subtitle: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        const SizedBox(height: 4.0),
                        Text(
                          user.lastMessage,
                          style: const TextStyle(
                            fontSize: 14.0,
                          ),
                        ),
                        const SizedBox(height: 4.0),
                        Text(
                          user.time,
                          style: const TextStyle(
                            fontSize: 12.0,
                            color: Colors.grey,
                          ),
                        ),
                      ],
                    ),
                    onTap: () async {
                      if (user.name == 'Maria') {
                        Navigator.push(
                          context,
                          MaterialPageRoute(builder: (context) => ChatMaria()),
                        );
                      }
                    },
                  ),
                ),
              ),
            );
          },
        ),
      ),
      bottomNavigationBar: NavBottom(
        selectedIndex: _selectedIndex,
        onItemTapped: _onItemTapped,
      ),
    );
  }
}

class NavBottom extends StatelessWidget {
  final int selectedIndex;
  final Function(int) onItemTapped;

  NavBottom({required this.selectedIndex, required this.onItemTapped});

  @override
  Widget build(BuildContext context) {
    return BottomNavigationBar(
      currentIndex: selectedIndex,
      onTap: onItemTapped,
      items: [
        BottomNavigationBarItem(
          icon: Icon(Icons.home),
          label: 'Home',
        ),
        BottomNavigationBarItem(
          icon: Icon(Icons.message),
          label: 'Messages',
        ),
        BottomNavigationBarItem(
          icon: Icon(Icons.call),
          label: 'Petsitter',
        ),
        BottomNavigationBarItem(
          icon: Icon(Icons.person),
          label: 'Perfil',
        ),
      ],
      selectedItemColor:
          Color.fromRGBO(255, 152, 84, 1), // Customize the selected item color
      unselectedItemColor: Colors.grey, // Customize the unselected item color
      backgroundColor: Colors.white, // Customize the background color
      elevation: 5, // Add elevation for a shadow effect
    );
  }
}

class User {
  final String name;
  final String lastMessage;
  final String time;
  final String imagePath;

  User({
    required this.name,
    required this.lastMessage,
    required this.time,
    required this.imagePath,
  });
}
