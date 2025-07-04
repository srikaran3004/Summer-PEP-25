
#!/usr/bin/env python3

import json
import time
from datetime import datetime
from kafka import KafkaProducer


class SimpleProducer:
    def __init__(self, bootstrap_servers=['localhost:9092'], topic='demo-topic'):
        self.topic = topic
        self.producer = KafkaProducer(
            bootstrap_servers=bootstrap_servers,
            value_serializer=lambda v: json.dumps(v).encode('utf-8'),
            key_serializer=lambda k: k.encode('utf-8') if k else None
        )
        print(f"Producer initialized for topic: {topic}")

    def send_message(self, message, key=None):
        """Send a single message to the Kafka topic"""
        try:
            future = self.producer.send(self.topic, value=message, key=key)
            record_metadata = future.get(timeout=10)
            print(f"Message sent to {record_metadata.topic} partition {record_metadata.partition} offset {record_metadata.offset}")
            return True
        except Exception as e:
            print(f"Failed to send message: {e}")
            return False

    def send_sample_messages(self, count=10):
        """Send sample messages for demonstration"""
        print(f"Sending {count} sample messages...")
        
        for i in range(count):
            message = {
                'id': i + 1,
                'message': f'Hello from producer! Message #{i + 1}',
                'timestamp': datetime.now().isoformat(),
                'user': f'user_{i % 3 + 1}'  # Rotate between user_1, user_2, user_3
            }
            
            key = f'key_{i + 1}'
            
            if self.send_message(message, key):
                print(f"✓ Sent: {message}")
            else:
                print(f"✗ Failed to send message {i + 1}")
            
            time.sleep(1)  # Wait 1 second between messages

    def close(self):
        """Close the producer connection"""
        self.producer.close()
        print("Producer closed")


def main():
    producer = SimpleProducer()
    
    try:
        print("=== Kafka Producer Demo ===")
        print("Choose an option:")
        print("1. Send sample messages automatically")
        print("2. Send custom messages interactively")
        
        choice = input("Enter your choice (1 or 2): ").strip()
        
        if choice == '1':
            count = input("How many messages to send? (default: 10): ").strip()
            count = int(count) if count.isdigit() else 10
            producer.send_sample_messages(count)
            
        elif choice == '2':
            print("Enter messages (type 'quit' to exit):")
            while True:
                message_text = input("Message: ").strip()
                if message_text.lower() == 'quit':
                    break
                
                key = input("Key (optional, press Enter to skip): ").strip()
                key = key if key else None
                
                message = {
                    'message': message_text,
                    'timestamp': datetime.now().isoformat()
                }
                
                producer.send_message(message, key)
        else:
            print("Invalid choice. Sending 5 sample messages...")
            producer.send_sample_messages(5)
            
    except KeyboardInterrupt:
        print("\nOperation cancelled by user")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        producer.close()


if __name__ == "__main__":
    main() 
