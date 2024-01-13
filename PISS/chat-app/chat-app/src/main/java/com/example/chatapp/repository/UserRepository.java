package com.example.chatapp.repository;

import com.example.chatapp.module.Status;
import com.example.chatapp.module.User;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface UserRepository extends JpaRepository<User, Long> {
    public List<User> findAllByStatus(Status status);
    public Optional<User> findUserByUsername(String username);
}
