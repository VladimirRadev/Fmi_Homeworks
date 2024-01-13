package com.example.chatapp.controller;

import com.example.chatapp.module.User;
import com.example.chatapp.service.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

import java.util.List;

@Controller
@RequiredArgsConstructor
public class UserController {

    private final UserService service;

    @MessageMapping("/user.register")
    @SendTo("/topic/public")
    public User addUser(@Payload User user) {
        service.saveUser(user);
        return user;
    }

    @MessageMapping("/user.login")
    @SendTo("/topic/public")
    public User logUser(@Payload User user) {
        return service.logUser(user);
    }

    @MessageMapping("/user.disconnectUser")
    @SendTo("/topic/public")
    public User disconnect(@Payload User user) {
        service.disconnect(user);
        return user;
    }

    @GetMapping("/users")
    public ResponseEntity<List<User>> findConnectedUserd() {
        return ResponseEntity.ok(service.getConnectedUsers());
    }
}
