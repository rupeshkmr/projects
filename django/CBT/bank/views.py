from django.shortcuts import render
from django.views.generic.edit import CreateView,UpdateView,DeleteView,FormView
from django.views.generic import ListView, DetailView
from django.http import Http404
from django.urls import reverse_lazy,reverse
from django.http import HttpResponseRedirect, HttpResponse
from datetime import date, timedelta
from django.shortcuts import redirect
from django.contrib.auth.decorators import user_passes_test
from django.utils.decorators import method_decorator
from django.contrib.auth.decorators import login_required
from .forms import *
from profile.models import UserProfile
from .models import Bank, BankAccount
today = date.today()


class BankDetails(DetailView):
	@method_decorator(user_passes_test(lambda u: u.is_authenticated))
	def dispatch(self, *args, **kwargs):
		return super().dispatch(*args, **kwargs)
	template_name = 'bank/bank_details.html'

	def get_context_data(self, **kwargs):
		context = super().get_context_data(**kwargs)
		context['object_list'] = BankAccount.objects.all()
		return context

	def get_object(self, *args, **kwargs):
		request = self.request
		id = self.kwargs.get('pk')
		try:
			instance = []
			instance.append(Bank.objects.get(id=id))
		except:
			raise Http404("Sorry Server Failure")
		return instance

class Credit(UpdateView):
	def user_passes_test(self, request):
		if request.user.is_authenticated:
			self.object = self.get_object()
			return self.object.user.user == request.user
		return False

	def dispatch(self, request, *args, **kwargs):
		if not self.user_passes_test(request):
			if request.user.is_authenticated:
				object = BankAccount.objects.get(user=UserProfile.objects.get(user=request.user))
				return redirect(reverse_lazy('bank:credit',kwargs={'pk':object.id}))
			else:
				return redirect('accounts:login')
		return super(Credit, self).dispatch(
			request, *args, **kwargs)
	model = BankAccount
	form_class = CreditForm
	template_name = 'bank/credit.html'
	def form_valid(self, form):
		obj = form.save(commit=False)
		bank = Bank.objects.first()
		bank.amount += obj.returnamt
		bank.save()
		obj.lastreturn = obj.returnamt
		obj.return_date = today
		obj.save()
		return redirect(reverse('bank:bankdetails',kwargs={'pk':1}))
	success_url = reverse_lazy('bank:bankdetails',kwargs={'pk':1})

class Invest(UpdateView):
	def user_passes_test(self, request):
		if request.user.is_authenticated:
			self.object = self.get_object()
			return self.object.user.user == request.user
		return False

	def dispatch(self, request, *args, **kwargs):
		if not self.user_passes_test(request):
			if request.user.is_authenticated:
				object = BankAccount.objects.get(user=UserProfile.objects.get(user=request.user))
				return redirect(reverse_lazy('bank:invest',kwargs={'pk':object.id}))
			else:
				return redirect('accounts:login')
		return super(Invest, self).dispatch(
			request, *args, **kwargs)

	model = BankAccount
	form_class = InvestForm
	template_name = 'bank/invest.html'
	def form_valid(self, form):
		obj = form.save(commit=False)
		bank = Bank.objects.first()
		bank.amount += obj.creditamt
		bank.totalinvested += bank.amount
		bank.save()
		obj.investment += obj.creditamt
		obj.lastcredit = obj.creditamt
		obj.investno += 1
		obj.shouldinvest = False
		obj.invest_date = today
		obj.save()
		return redirect(reverse('bank:bankdetails',kwargs={'pk':1}))
	success_url = reverse_lazy('bank:bankdetails',kwargs={'pk':1})

class Debit(UpdateView):
	def user_passes_test(self, request):
		if request.user.is_authenticated:
			self.object = self.get_object()
			return self.object.user.user == request.user
		return False

	def dispatch(self, request, *args, **kwargs):
		if not self.user_passes_test(request):
			if request.user.is_authenticated:
				object = BankAccount.objects.get(user=UserProfile.objects.get(user=request.user))
				return redirect(reverse_lazy('bank:debit',kwargs={'pk':object.id}))
			else:
				return redirect('accounts:login')
		return super(Debit, self).dispatch(
			request, *args, **kwargs)

	model = BankAccount
	form_class = DebitForm
	template_name = 'bank/debit.html'
	def form_valid(self, form):
		obj = form.save(commit=False)
		bank = Bank.objects.first()
		if (bank.amount < obj.debitamt):
			raise Http404('Sorry Not Enough Balance')
		bank.amount -= obj.debitamt
		bank.save()
		obj.lastdebit = obj.debitamt
		obj.save()
		return redirect(reverse('bank:bankdetails',kwargs={'pk':1}))
	success_url = reverse_lazy('bank:bankdetails',kwargs={'pk':1})


class Loan(UpdateView):
	def user_passes_test(self, request):
		if request.user.is_authenticated:
			self.object = self.get_object()
			return self.object.user.user == request.user
		return False

	def dispatch(self, request, *args, **kwargs):
		if not self.user_passes_test(request):
			if request.user.is_authenticated:
				object = BankAccount.objects.get(user=UserProfile.objects.get(user=request.user))
				return redirect(reverse_lazy('bank:loan',kwargs={'pk':object.id}))
			else:
				return redirect('accounts:login')
		return super(Loan, self).dispatch(
			request, *args, **kwargs)

	model = BankAccount
	form_class = LoanForm
	template_name = 'bank/loan.html'
	def form_valid(self, form):
		obj = form.save(commit=False)
		bank = Bank.objects.first()
		if(bank.amount<obj.loan):
			raise Http404('Sorry Not Enough Balance')
		bank.amount -= obj.loan
		bank.save()
		obj.loan_date = today
		obj.save()
		return redirect(reverse('bank:bankdetails',kwargs={'pk':1}))
	success_url = reverse_lazy('bank:bankdetails',kwargs={'pk':1})