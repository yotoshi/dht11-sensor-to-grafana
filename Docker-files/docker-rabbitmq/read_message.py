import pika, sys, os

def main():
    #Paramètre de connexion avec notre rabbitMQ
    credentials=pika.PlainCredentials('rabbitmq','rabbitmq') #username + password
    connection = pika.BlockingConnection(pika.ConnectionParameters('localhost',5672,'/',credentials))#connexion à l'api sur le port 5672 et non à l'interface web 15672
    channel = connection.channel()
    # la fonction call_back nous permet d'afficher sur la console sur contenu du message. Elle est propre a la librairie pika
    def callback(ch, method, properties, body):
        print(" [x] Received %r" % body)
    #Basic_consume est la fonction de pika qui permet de lire les messages dans la queue fournis en argument
    #on_message_callback permet de faire appel a notre fonction call_back qui va afficher le contenu du message
   
    channel.basic_consume(queue='slow', on_message_callback=callback)

    print(' [*] Waiting for messages. To exit press CTRL+C')
    channel.start_consuming()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)