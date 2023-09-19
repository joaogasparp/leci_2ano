import 'package:flutter/material.dart';
import 'package:petsportal/chatPagePetsitter.dart';
import 'package:petsportal/homePetsitterPage.dart';
import 'profilePetsitterPage.dart';

class ordersPage extends StatefulWidget {
  @override
  _ordersPageState createState() => _ordersPageState();
}

class _ordersPageState extends State<ordersPage> {
  int _selectedIndex = 2;

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
    if (_selectedIndex == 0) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => HomePagePetSitter()),
      );
    }
    if (_selectedIndex == 1) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => ChatPagePetsitter()),
      );
    }
    if (_selectedIndex == 2) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => ordersPage()),
      );
    }
    if (_selectedIndex == 3) {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => profilePetsitterPage()),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        automaticallyImplyLeading: false, // Remove the back button
        title: const Text(
          'Orders',
          style: TextStyle(
            fontWeight: FontWeight.bold,
            fontSize: 20.0,
          ),
        ),
        backgroundColor: Color.fromRGBO(255, 152, 84, 1),
        elevation: 0,
      ),
      body: Center(
        child: Text(
          'Welcome to the orders page!',
          style: TextStyle(fontSize: 24.0),
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
