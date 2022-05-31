```

int main()
{  
     

	SimpleServer::Server app;

	app.Get("/api", [](ResponseWriter& rw, RequestDetails& r) {
		rw.SetJsonContent("{\"success\": \"true\"}");
	});

	app.Get("/", []() {
		return "Home";
	});

	app.Get("/about", [](ResponseWriter& rw, RequestDetails& r) {
		rw.SetContent("About");
     });

	app.Get("/feed", [](ResponseWriter& rw, RequestDetails& r) {
		rw.SetContent(
			"<html>"
			"<body>"
			"<h1>Hello World</h1>"
			"<button onclick='add()'>+</button>"
			"<h1 id='counter'>0</h1>"
			"<button onclick='sub()'>-</button>"
			"<script>"
			"let c = document.querySelector('#counter');"
			"function add(){c.textContent = parseInt(c.textContent) +1}"
			"function sub(){c.textContent = parseInt(c.textContent) -1}"
			"</script>"
			"</body>"
			"</html>"
		);
	});


	app.Run();

	return 0;

}



```