
#!/usr/bin/env python3

import json
from datetime import datetime
from kafka import KafkaConsumer


class SimpleConsumer:
    def __init__(self, bootstrap_servers=['localhost:9092'], topic='demo-topic', group_id='demo-group'):
        self.topic = topic
        self.group_id = group_id
        
        self.consumer = KafkaConsumer(
            topic,
            bootstrap_servers=bootstrap_servers,
            group_id=group_id,
            value_deserializer=lambda m: json.loads(m.decode('utf-8')),
            key_deserializer=lambda k: k.decode('utf-8') if k else None,
            auto_offset_reset='earliest',  # Start from the beginning if no offset is stored
            enable_auto_commit=True
        )
        
        print(f"Consumer initialized for topic: {topic} with group_id: {group_id}")

    def consume_messages(self):
        """Consume messages from the Kafka topic"""
        print(f"Starting to consume messages from topic '{self.topic}'...")
        print("Press Ctrl+C to stop consuming\n")
        
        try:
            message_count = 0
            for message in self.consumer:
                message_count += 1
                
                # Extract message details
                key = message.key
                value = message.value
                partition = message.partition
                offset = message.offset
                timestamp = datetime.fromtimestamp(message.timestamp / 1000).isoformat()
                
                print(f"=== Message #{message_count} ===")
                print(f"Key: {key}")
                print(f"Value: {json.dumps(value, indent=2)}")
                print(f"Partition: {partition}")
                print(f"Offset: {offset}")
                print(f"Timestamp: {timestamp}")
                print("-" * 40)
                
                # Process the message (you can add your custom logic here)
                self.process_message(key, value)
                
        except KeyboardInterrupt:
            print(f"\nConsumer stopped. Processed {message_count} messages.")
        except Exception as e:
            print(f"Error consuming messages: {e}")

    def process_message(self, key, value):
        """Process individual messages - customize this method for your use case"""
        if isinstance(value, dict):
            if 'user' in value:
                print(f"Processing message from {value['user']}: {value.get('message', 'No message content')}")
            else:
                print(f"Processing message: {value.get('message', 'No message content')}")
        else:
            print(f"Processing raw message: {value}")

    def close(self):
        """Close the consumer connection"""
        self.consumer.close()
        print("Consumer closed")


def main():
    print("=== Kafka Consumer Demo ===")
    
    # Allow user to specify custom topic and group_id
    topic = input("Enter topic name (default: demo-topic): ").strip()
    topic = topic if topic else 'demo-topic'
    
    group_id = input("Enter consumer group ID (default: demo-group): ").strip()
    group_id = group_id if group_id else 'demo-group'
    
    consumer = SimpleConsumer(topic=topic, group_id=group_id)
    
    try:
        consumer.consume_messages()
    except Exception as e:
        print(f"Error: {e}")
    finally:
        consumer.close()


if __name__ == "__main__":
    main() 
