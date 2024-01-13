package com.example.chatapp.service;

import com.example.chatapp.module.Status;
import com.example.chatapp.module.User;
import com.example.chatapp.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class UserService {
    private final UserRepository repository;

    public void saveUser(User user) {
        repository.save(user);
    }

    public void disconnect(User user) {
        User currUser = repository.findById(user.getId()).orElse(null);
        if(currUser != null) {
            currUser.setStatus(Status.OFFLINE);
            repository.save(currUser);
        }
    }

    public List<User> getConnectedUsers() {
        return repository.findAllByStatus(Status.ONLINE);
    }

    public User logUser(User user) {
        Optional<User> userOptional = repository.findUserByUsername(user.getUsername());
        return userOptional.orElse(null);
    }
}
