package com.example.chatapp.chat;

import lombok.*;

import javax.annotation.processing.Generated;
import java.awt.*;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class ChatMessage {
    private String content;
    private String sender;
    private MessageType type;
}
