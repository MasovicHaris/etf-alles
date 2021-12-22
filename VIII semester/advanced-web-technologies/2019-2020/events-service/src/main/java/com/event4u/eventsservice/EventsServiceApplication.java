package com.event4u.eventsservice;
import com.event4u.eventsservice.model.*;
import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.repository.*;
import com.event4u.eventsservice.service.EventService;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.netflix.discovery.converters.Auto;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.core.TopicExchange;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.listener.SimpleMessageListenerContainer;
import org.springframework.amqp.rabbit.listener.adapter.MessageListenerAdapter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.netflix.eureka.EnableEurekaClient;
import org.springframework.context.annotation.Bean;
import java.awt.*;
import java.time.LocalDate;
import java.time.LocalTime;

@EnableEurekaClient
@SpringBootApplication
public class EventsServiceApplication {
	static final String queueName = "events-notifications";
	public enum Status {CREATE_STARTED, CREATE_FINISHED, CREATE_FAILED, CREATE_FAILED_AGAIN};
	@Autowired
	Sender sender;
	private static final Logger log =
			LoggerFactory.getLogger(EventsServiceApplication.class);
	public static void main(String[] args) {
		SpringApplication.run(EventsServiceApplication.class, args);
	}
	@Bean
	Queue queue() {
		return new Queue(queueName, false);
	}
	@Bean
	Queue queueNE() {return new Queue("notification-events", false); }
	@Bean
	SimpleMessageListenerContainer container(ConnectionFactory connectionFactory,
											 MessageListenerAdapter listenerAdapter) {
		SimpleMessageListenerContainer container = new SimpleMessageListenerContainer();
		container.setConnectionFactory(connectionFactory);
		container.setQueueNames("notifications-events");
		container.setMessageListener(listenerAdapter);
		return container;
	}
	@Bean
	MessageListenerAdapter listenerAdapter(Receiver receiver) {
		return new MessageListenerAdapter(receiver, "listen");
	}
	@Bean
	TopicExchange exchange()
	{
		return new TopicExchange("message_queue_exchange");
	}
	@Bean
	Binding binding(Queue queue, TopicExchange exchange)
	{
		return BindingBuilder.bind(queue).to(exchange).with(queueName);
	}

	@Autowired
	EventService eventService;

	@JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "dd/MM/yyyy")
	@Bean
	public CommandLineRunner demo(CategoryRepository cRepository, UserRepository uRepository, LocationRepository lRepository, EventRepository eRepository, EventUserRepository euRepository) {
		return (args) -> {
			Category c1 = cRepository.save(new Category("Outdoors&Adventure", "o&a.jpg", "#2ecc71"));
			cRepository.save(new Category("Tech", "tech.jpg", "#1abc9c"));
			cRepository.save(new Category("Learning", "learning.jpg", "#3498db"));
			cRepository.save(new Category("Sport&Fitness", "s&f.jpg", "#9b59b6"));
			cRepository.save(new Category("Music", "music.jpg", "#34495e"));
			cRepository.save(new Category("Art", "art.jpg", "#f1c40f"));
			cRepository.save(new Category("Dance", "dance.jpg", "#e74c3c"));
			cRepository.save(new Category("Games", "games.jpg", "#d35400"));
			cRepository.save(new Category("Other", "other.jpg", "#7f8c8d"));
			log.info("Categories found with findAll():");
			log.info("-------------------------------");
			for (Category c : cRepository.findAll()) {
				log.info(c.toString());
			}
			log.info("");
			Long id = Long.valueOf(1);
			User u1 = uRepository.save(new User(id));
			User u2 = uRepository.save(new User(++id));
			User u3 = uRepository.save(new User(++id));
			uRepository.save(new User(++id));
			log.info("Users found with findAll():");
			log.info("-------------------------------");
			for (User u: uRepository.findAll()) {
				log.info(u.toString());
			}
			log.info("");
			Location l1 = lRepository.save(new Location(new Point(0,0), "Sarajevo", "Bosna i Hercegovina"));
			lRepository.save(new Location(new Point(0,0), "Mostar", "Bosna i Hercegovina"));
			lRepository.save(new Location(new Point(0,0), "Banja Luka", "Bosna i Hercegovina"));
			log.info("Locations found with findAll():");
			log.info("-------------------------------");
			for (Location l: lRepository.findAll()) {
				log.info(l.toString());
			}
			log.info("");
			Event e1 = eRepository.save(new Event("Studentski pohodi - Bobovac",
					"Bobovac",
					LocalDate.of(2021, 3, 1),
					"Pridružite nam se na pohodu na Bobovac. Pohod je 15KM, u cijenu je uračunat prevoz i vodič. Na pohod polazimo u 8:00 sati i okupljamo se na kampusu UNSA-e!!!",
					Boolean.TRUE,
					c1,
					u1,
					l1,
					"https://storage.googleapis.com/event4u-d02b0.appspot.com/1609713991787_bobovac.jpg",
					"08:00",
					"18:00",
					null
			));
			eventService.changeStatus(e1.getId(),Status.CREATE_FINISHED);
			Event e2 = eRepository.save(
					new Event("Studentski pohodi - Trebević",
							"Trebevic",
							LocalDate.of(2021, 2, 20),
							"Pridružite nam se u subotu na pohodu na Trebević. Pohod je besplatan, od Vas se traži samo da ponesete dobro raspoloženje :) Na Trebević polazimo u 8:30 sati i okupljamo se na LATINSKOJ ĆUPRIJI!!!",
							Boolean.TRUE,
							c1,
							u1,
							l1,
							"https://storage.googleapis.com/event4u-d02b0.appspot.com/1609714113829_trebevic.jpg",
							"08:30",
							"20:00",
							null
					));
			Event e3 = eRepository.save(
					new Event("Čvrsnica ultra trail 2021.",
							"Čvrsnica",
							LocalDate.of(2021, 8, 28),
							"Čvrsnica Ultra Trail, planinska utrka koja će vas odvesti na Čvrsnicu „svetu“ planinu Hercegovine koje je prožeta poviješću uklesanoj kako prirodom tako i ljudskom rukom. Na ovoj utrci ćete protrčati pored prirodnog fenomena Hajdučkih kao i najviših vrhova Pločno (2228 mnv) i Veliki Vilinac (2118 mnv) koji će vas natjerati da s poštovanjem prođete preko ovih hercegovačkih divova.\n" +
									"Čvrsnica Ultra Trail održava se 28.8.2021. godine u 8:30 u Parku prirode Blidinje koji se nalazi u Hercegovini u području visokog gorja središnjih Dinarida. Pozivamo sve zaljubljenike u planine da dođu i natope znojem žedni hercegovački kamen.",
							Boolean.TRUE,
							c1,
							u2,
							l1,
							"http://www.shiftbranddesign.com/sites/default/files/slike/galerija/1_900x600_majica_dizajn_logotipa_cut.gif.png",
							"08:30",
							"20:00",
							null
					));
			Event e4 = eRepository.save(
					new Event("ZIMSKI BREAK 2021",
							"Rumija",
							LocalDate.of(2021, 3, 28),
							"ZIMSKI BREAK 2021. vodi nas na planine Rumija u Crnoj Gori i Leotar u Bosni i Hercegovini.\n" +
									"Rumija je planina na jugu Crne Gore, smještena između Jadrana i Skadarskog jezera. Najviša tačka je Rumija, koja je visoka 1.594 m. Rumija se uzdiže iznad grada Bara i prirodna je dinarska barijera, odvajajući Jadran od Skadarskog jezera.\n" +
									"Leotar je planina koja se uzdiže iznad Trebinja. Najviši vrh Leotara se nalazi na nadmorskoj visini od 1244 metara. Plan puta:\n" +
									"Petak, 28.03.2021. - Polazak u 13,00h ispred Zemaljskog muzeja. Dolazak u Bar oko 18,00 časova. Smještaj u sobe.\n" +
									"Subota, 29.03.2021. - Rano ustajanje, polazak na uspon na Rumiju u 7,00h. Povratak sa uspona, slobodno vrijeme.\n" +
									"Nedjelja, 30.03.2021. - Polazak iz Bara u 6,00h. Dolazak u Trebinje i uspon na Leotar. Po povratku kraći obilazak Trebinja (Arslanagića most i dr.). Nastavak putovanja za Sarajevo. Povratak u Sarajevu u ranim večernjim časovima.",
							Boolean.TRUE,
							c1,
							u3,
							l1,
							"https://www.photomontenegro.me/wp-content/gallery/planine//mountains-rumija-9.jpg",
							"13:00",
							"20:00",
							null
					));
			eventService.changeStatus(e2.getId(),Status.CREATE_FINISHED);
			eventService.changeStatus(e3.getId(),Status.CREATE_FINISHED);
			eventService.changeStatus(e4.getId(),Status.CREATE_FINISHED);
			log.info("Events found with findAll():");
			log.info("-------------------------------");
			for (Event e: eRepository.findAll()) {
				log.info(e.toString());
			}
			log.info("");
			euRepository.save(new EventUser(u2, e1, Boolean.TRUE));
			e1.addGoing();
			eRepository.save(e1);
			log.info("Event-User found with findAll():");
			log.info("-------------------------------");
			for (EventUser eu: euRepository.findAll()) {
				log.info(eu.toString());
			}
			log.info("");
			/*String command =
					"curl -i -H \"Content-Type: application/json\" -d '{\"title\": \"LV5 NWT\",\"address\": \"Zmaja od Bosne bb\",\"date\": \"2020-03-21\",\"description\": \"Laboratorijske vježbe iz predmeta NWT\",\"idCategory\": 1,\"idUser\": 5,\"idLocation\": 7}' http://localhost:8080/events-micro/events";
			ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));*/
		};
	}
}