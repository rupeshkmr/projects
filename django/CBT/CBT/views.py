from django.http import HttpResponse
from django.shortcuts import render, redirect
from django.urls import reverse_lazy, reverse


def home_page(request):
	# print(request.session.get("first_name","Unknown")) # getter
	context = {
		"title": "Hello World",
		"content": "Welcome to homepage",
		# "premium_content":"YEAHHHH"
	}  # render:Renders html pages requires 3 parameters request,template,context(dictionary)
	if request.user.is_authenticated:
		context["premium_content"] = "YEAHHH"

	# if request.user.is_admin:
	# 	context["superuser"] = "Welcome Sir"
	return render(request, "home_page.html", context)


