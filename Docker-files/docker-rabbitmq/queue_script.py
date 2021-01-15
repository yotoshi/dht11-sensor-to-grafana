import pika

credentials=pika.PlainCredentials('rabbitmq','rabbitmq')
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost',5672,'/',credentials))
channel = connection.channel()

channel.exchange_declare(exchange='client1',exchange_type='direct')
channel.queue_declare(queue='slow')
channel.queue_declare(queue='fast')

channel.queue_bind(exchange='client1',queue='slow',routing_key='slow')
channel.queue_bind(exchange='client1',queue='fast',routing_key='fast')
