import 'package:flutter/material.dart';

class ChatMaria extends StatefulWidget {
  @override
  _ChatMariaState createState() => _ChatMariaState();
}

class _ChatMariaState extends State<ChatMaria> {
  final List<Message> messages = [
    Message(sender: 'Maria', content: 'Olá, como está?'),
  ];

  TextEditingController _textEditingController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(
          'Maria',
          style: TextStyle(
            fontWeight: FontWeight.bold,
          ),
        ),
        backgroundColor: Color.fromRGBO(255, 152, 84, 1),
      ),
      body: Column(
        children: <Widget>[
          Expanded(
            child: ListView.builder(
              itemCount: messages.length,
              itemBuilder: (context, index) {
                final message = messages[index];
                return message.sender == 'Maria'
                    ? _buildReceivedMessage(message)
                    : _buildSentMessage(message);
              },
            ),
          ),
          _buildMessageInputField(),
        ],
      ),
    );
  }

  Widget _buildReceivedMessage(Message message) {
    return Padding(
      padding: const EdgeInsets.fromLTRB(16.0, 20.0, 16.0, 0.0),
      child: Align(
        alignment: Alignment.centerLeft,
        child: Container(
          padding: EdgeInsets.all(8.0),
          decoration: BoxDecoration(
            color: Color.fromARGB(255, 210, 210, 210),
            borderRadius: BorderRadius.circular(8.0),
          ),
          child: Text(
            message.content,
            style: TextStyle(
              fontSize: 16.0,
              color: Colors.black,
            ),
          ),
        ),
      ),
    );
  }

  Widget _buildSentMessage(Message message) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 8.0),
      child: Align(
        alignment: Alignment.centerRight,
        child: Container(
          padding: EdgeInsets.all(8.0),
          decoration: BoxDecoration(
            color: Color.fromRGBO(255, 152, 84, 1),
            borderRadius: BorderRadius.circular(8.0),
          ),
          child: Text(
            message.content,
            style: TextStyle(
              fontSize: 16.0,
              color: Colors.white,
            ),
          ),
        ),
      ),
    );
  }

  Widget _buildMessageInputField() {
    return Container(
      padding: EdgeInsets.all(8.0),
      child: Row(
        children: <Widget>[
          Expanded(
            child: TextField(
              controller: _textEditingController,
              decoration: InputDecoration(
                hintText: 'Type a message...',
                border: OutlineInputBorder(),
              ),
            ),
          ),
          SizedBox(width: 8.0),
          IconButton(
            icon: Icon(Icons.send),
            onPressed: () {
              String content = _textEditingController.text.trim();
              if (content.isNotEmpty) {
                setState(() {
                  messages.add(Message(sender: 'User', content: content));
                  _textEditingController.clear();
                });

                _simulateResponse();
              }
            },
          ),
        ],
      ),
    );
  }

  void _simulateResponse() {
    Future.delayed(Duration(seconds: 2), () {
      setState(() {
        messages.add(Message(
            sender: 'Maria', content: 'Estou ótima. Em que posso ajudar?'));
      });
    });
  }
}

class Message {
  final String sender;
  final String content;

  Message({required this.sender, required this.content});
}
