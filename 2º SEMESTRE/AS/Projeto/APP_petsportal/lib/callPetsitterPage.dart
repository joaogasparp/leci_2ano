import 'package:flutter/material.dart';
import 'package:petsportal/profileUserPage.dart';
import 'chatPage.dart';
import 'choosePetsitterPage.dart';
import 'homeUser.dart';
import 'package:google_maps_flutter/google_maps_flutter.dart';

class callPetsitterPage extends StatefulWidget {
  @override
  _callPetsitterPage createState() => _callPetsitterPage();
}

class _callPetsitterPage extends State<callPetsitterPage> {
  int _selectedIndex = 2;

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
      // Check if the "Messages" item is tapped (index 1)
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
          'Petsitting',
          style: TextStyle(
            fontWeight: FontWeight.bold,
            fontSize: 20.0,
          ),
        ),
        backgroundColor: Color.fromRGBO(255, 152, 84, 1),
        elevation: 0,
      ),
      body: MapScreen(),
      bottomNavigationBar: NavBottom(
        selectedIndex: _selectedIndex,
        onItemTapped: _onItemTapped,
      ),
    );
  }
}

void showPriceMessage(BuildContext context) {
  showDialog(
    context: context,
    builder: (BuildContext context) {
      return AlertDialog(
        title: Text('Calculated price:'),
        content: Text('5.63€\n\n Arriving in: 2min'),
        actions: <Widget>[
          ElevatedButton(
            child: Text('Choose Petsitter'),
            onPressed: () {
              // Action for choosing petsitter
              Navigator.push(
                context,
                MaterialPageRoute(builder: (context) => choosePetsitterPage()),
              );
            },
          ),
          ElevatedButton(
            child: Text('Cancel'),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      );
    },
  );
}

class MapScreen extends StatelessWidget {
  final LatLng initialCameraPosition =
      LatLng(41.145622, -8.610878); // Initial map center

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Stack(
        children: [
          GoogleMap(
            initialCameraPosition: CameraPosition(
              target: initialCameraPosition,
              zoom: 15.0,
            ),
            markers: {
              Marker(
                markerId: MarkerId('marker_id'),
                position: initialCameraPosition,
                infoWindow: InfoWindow(
                  title: 'Localização atual',
                  snippet: '',
                ),
              ),
              Marker(
                markerId: MarkerId('marker_id'),
                position: LatLng(41.144975, -8.611778),
                infoWindow: InfoWindow(
                  title: 'Petsitter',
                  snippet: 'distância: 700m',
                ),
              ),
              Marker(
                markerId: MarkerId('marker_id'),
                position: LatLng(41.146104, -8.611280),
                infoWindow: InfoWindow(
                  title: 'Petsitter',
                  snippet: 'distância: 300m',
                ),
              ),
              Marker(
                markerId: MarkerId('marker_id'),
                position: LatLng(41.149269, -8.610828),
                infoWindow: InfoWindow(
                  title: 'Call Button',
                  snippet: 'distância: 1.1Km',
                ),
              ),
            },
            onMapCreated: (GoogleMapController controller) {},
          ),
          Positioned(
            left: 0,
            right: 0,
            bottom: 16.0,
            child: Center(
              child: ElevatedButton(
                style: ElevatedButton.styleFrom(
                  backgroundColor: Color.fromARGB(255, 12, 178, 238),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(20.0),
                  ),
                  fixedSize:
                      Size(200.0, 30.0), // Set the fixed width and height
                ),
                onPressed: () {
                  showPriceMessage(context);
                },
                child: Text('Call Petsitter'),
              ),
            ),
          ),
        ],
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
