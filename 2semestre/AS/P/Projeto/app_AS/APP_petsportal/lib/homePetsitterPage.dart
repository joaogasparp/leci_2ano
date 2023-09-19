import 'package:flutter/material.dart';
import 'package:petsportal/profilePetsitterPage.dart';
import 'package:petsportal/profileUserPage.dart';
import 'callPetsitterPage.dart';
import 'chatPage.dart';

class HomePagePetSitter extends StatefulWidget {
  @override
  _HomePagePetSitter createState() => _HomePagePetSitter();
}

class User {
  final String name;
  final String lastMessage;
  final String imagePath;
  final String publicationImage;

  User({
    required this.name,
    required this.lastMessage,
    required this.imagePath,
    required this.publicationImage,
  });
}

class _HomePagePetSitter extends State<HomePagePetSitter> {
  final List<User> users = [
    User(
      name: 'João',
      lastMessage: 'Uma manhã bem começada!',
      imagePath: 'assets/jonh.png',
      publicationImage: 'assets/publication1.jpg',
    ),
    User(
      name: 'Maria',
      lastMessage: 'Coisita mais fofinhaaaa...',
      imagePath: 'assets/maria.jpg',
      publicationImage: 'assets/publication2.jpg',
    ),
    User(
      name: 'Helena',
      lastMessage: 'Ontem ele ficou assim a olhar para mim',
      imagePath: 'assets/emily.jpg',
      publicationImage: 'assets/publication3.jpg',
    ),
  ];

  List<bool> isLiked = [false, false, false];
  String searchQuery = '';

  List<User> filteredUsers = [];

  @override
  void initState() {
    super.initState();
    filterUsers();
  }

  void filterUsers() {
    filteredUsers = users.where((user) {
      final lowercaseQuery = searchQuery.toLowerCase();
      final lowercaseName = user.name.toLowerCase();
      final lowercaseLastMessage = user.lastMessage.toLowerCase();

      return lowercaseName.contains(lowercaseQuery) ||
          lowercaseLastMessage.contains(lowercaseQuery);
    }).toList();
  }

  int _selectedIndex = 0;

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
          'Home Page',
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
        child: Column(
          children: [
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: TextField(
                onChanged: (value) {
                  setState(() {
                    searchQuery = value;
                    filterUsers();
                  });
                },
                decoration: InputDecoration(
                  hintText: 'Search',
                  prefixIcon: Icon(Icons.search),
                  border: OutlineInputBorder(
                    borderRadius: BorderRadius.circular(10.0),
                  ),
                ),
              ),
            ),
            Expanded(
              child: filteredUsers.isEmpty
                  ? Center(
                      child: Text(
                        'Não foram encontrados resultados para a sua pesquisa.',
                        style: TextStyle(
                          fontSize: 16.0,
                          fontWeight: FontWeight.bold,
                        ),
                      ),
                    )
                  : ListView.builder(
                      padding: EdgeInsets.symmetric(vertical: 10.0),
                      itemCount: filteredUsers.length,
                      itemBuilder: (context, index) {
                        final user = filteredUsers[index];
                        return Padding(
                          padding: const EdgeInsets.symmetric(
                              vertical: 8.0, horizontal: 16.0),
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
                                    Image.asset(user.publicationImage),
                                    Row(
                                      children: [
                                        IconButton(
                                          icon: Icon(
                                            isLiked[index]
                                                ? Icons.favorite
                                                : Icons.favorite_border,
                                            color: Colors.red,
                                          ),
                                          onPressed: () {
                                            setState(() {
                                              isLiked[index] = !isLiked[index];
                                            });
                                          },
                                        ),
                                        Text(
                                          isLiked[index] ? 'Liked' : 'Like',
                                        ),
                                      ],
                                    ),
                                  ],
                                ),
                              ),
                            ),
                          ),
                        );
                      },
                    ),
            ),
          ],
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
