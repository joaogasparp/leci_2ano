import 'package:flutter/material.dart';
import 'package:google_maps_flutter/google_maps_flutter.dart';

class choosePetsitterPage extends StatefulWidget {
  const choosePetsitterPage({super.key});

  @override
  State<choosePetsitterPage> createState() => _choosePetsitterPageState();
}

class _choosePetsitterPageState extends State<choosePetsitterPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(body: MapScreen());
  }
}

class MapScreen extends StatelessWidget {
  final LatLng initialCameraPosition =
      LatLng(41.145622, -8.610878); // Initial map center

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'Tracking Page',
          style: TextStyle(
            fontWeight: FontWeight.bold,
            fontSize: 20.0,
          ),
        ),
        backgroundColor: Color.fromRGBO(255, 152, 84, 1),
        elevation: 0,
      ),
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
                  snippet: 'distância: 300m',
                ),
              ),
            },
            onMapCreated: (GoogleMapController controller) {},
          ),
          Positioned(
            top: 0,
            left: 0,
            right: 0,
            child: Container(
              color: Color.fromARGB(255, 255, 255, 255),
              padding: EdgeInsets.all(16.0),
              child: Text(
                'Thank you for your trust!\n\nMaria will take care of your pet. \n\nIn the map you can keep track of your pet while you are away.',
                style: TextStyle(
                  fontSize: 18.0,
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }
}
