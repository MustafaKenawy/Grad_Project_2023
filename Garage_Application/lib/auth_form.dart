

import 'package:flutter/material.dart';

// ignore_for_file: prefer_const_constructors

class AuthForm extends StatefulWidget {
  AuthForm(this.submiting, this._isLoading);


  bool _isLoading;
  void Function(String userName, String Password, String email,bool isLogin,
      BuildContext ctx,String carNumber ) submiting;

  @override
  State<AuthForm> createState() => _AuthFormState();
}

class _AuthFormState extends State<AuthForm> {
  final _formKey = GlobalKey<FormState>();
  var _userName = '';
  var _password = '';
  var _email = '';
  var _carNumber='';

  var _isLogin = true;


  void _trySubmit()  {
    FocusScope.of(context).unfocus();
    var _state = _formKey.currentState;
    if (_state != null && _state.validate()) {
      _state.save();
      widget.submiting(_userName, _password, _email.trim(), _isLogin, context,_carNumber);
    }
  }

  void _switch() {
    setState(() {
      _isLogin = !_isLogin;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        gradient: LinearGradient(
          begin: Alignment.topLeft,
          end: Alignment.bottomRight, //(.8, 1),
          colors: [
            Theme.of(context).colorScheme.secondary,
            Theme.of(context).colorScheme.primary,
          ],
        ),
      ),
      child: Center(
        child: Card(
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(25),
          ),
          elevation: 15,
          margin: EdgeInsets.all(20),
          child: SingleChildScrollView(
            padding: EdgeInsets.all(25),
            child: Form(
              key: _formKey,
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  TextFormField(
                    validator: (value) {
                      if (value != null) {
                        if (value.isEmpty || !value.contains('@')) {
                          return 'Enter a valid Email address !!';
                        }
                      }
                      return null;
                    },
                    key: ValueKey('email'),
                    keyboardType: TextInputType.emailAddress,
                    decoration: InputDecoration(
                      labelText: 'Email',
                    ),
                    onSaved: (value) {
                      _email = value!;
                    },
                  ),
                  SizedBox(
                    height: 10,
                  ),
                  if (!_isLogin)
                    TextFormField(
                      validator: (value) {
                        if (value != null) {
                          if (value.isEmpty || value.length < 4) {
                            return 'must be at least 4 chars';
                          }
                        }
                        return null;
                      },
                      key: ValueKey('Username'),
                      keyboardType: TextInputType.text,
                      decoration: InputDecoration(labelText: 'UserName'),
                      onSaved: (value) {
                        _userName = value!;
                      },
                    ),
                  SizedBox(
                    height: 10,
                  ),
                  TextFormField(
                    validator: (value) {
                      if (value != null) {
                        if (value.isEmpty || value.length < 7) {
                          return 'must be at least 7 chars';
                        }
                      }
                      return null;
                    },
                    key: ValueKey('Password'),
                    obscureText: true,
                    keyboardType: TextInputType.text,
                    decoration: InputDecoration(labelText: 'Password'),
                    onSaved: (value) {
                      _password = value!;
                    },
                  ),
                  if (!_isLogin)
                  SizedBox(height: 10,),
                  if (!_isLogin)
                  TextFormField(
                    validator: (value) {
                      if (value != null) {
                        if (value.isEmpty || value.length < 7 || value.length>10) {
                          return 'invalid number example: "8321 م ل ب"';
                        }
                      }
                      return null;
                    },
                    key: ValueKey('Car Number'),
                    keyboardType: TextInputType.text,
                    decoration: InputDecoration(labelText: 'Car Number'),
                    onSaved: (value) {
                      _carNumber = value!;
                    },

                  ),
                  SizedBox(
                    height: 20,
                  ),
                  if (!widget._isLoading)
                    ElevatedButton(
                      style: ButtonStyle(
                        elevation: MaterialStateProperty.all(7),
                        shape: MaterialStateProperty.all(
                          RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(25),
                          ),
                        ),
                      ),
                      onPressed: _trySubmit,
                      child: _isLogin
                          ? Text(
                        'login',
                        style: TextStyle(fontSize: 17),
                      )
                          : Text(
                        'Sign Up',
                        style: TextStyle(fontSize: 17),
                      ),
                    ),
                  if (!widget._isLoading)
                    TextButton(
                        onPressed: _switch,
                        child: _isLogin
                            ? Text(
                          'Sign up',
                          style: TextStyle(
                            fontSize: 15,
                          ),
                        )
                            : Text(
                          'Already has an account',
                          style: TextStyle(
                            fontSize: 15,
                          ),
                        )),
                  if (widget._isLoading) CircularProgressIndicator(),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}
