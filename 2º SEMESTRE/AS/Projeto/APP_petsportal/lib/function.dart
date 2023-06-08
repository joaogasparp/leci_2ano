import 'dart:convert';

import 'package:http/http.dart' as http;

fetchdata(String url) async {
  http.Response response = await http.get(Uri.parse(url));
  return response.body;
}

Future<http.Response> login(
    String apiUrl, String username, String password) async {
  final headers = {'Content-Type': 'application/json'};
  final body = jsonEncode({'username': username, 'password': password});

  final response =
      await http.post(Uri.parse(apiUrl), headers: headers, body: body);

  return response;
}
