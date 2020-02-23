from django import forms
from django.forms import ModelForm
from django.contrib.auth.models import User
from .models import Bank,BankAccount
class CreditForm(forms.ModelForm):
	class Meta:
		model = BankAccount
		fields = ('returnamt',)
		widgets = {
			'returnamt': forms.NumberInput(attrs={'class':'form-control','placeholder':'Enter Amount'})
		}

class InvestForm(forms.ModelForm):
	class Meta:
		model = BankAccount
		fields = ('creditamt',)
		widgets = {
			'creditamt': forms.NumberInput(attrs={'class':'form-control','placeholder':'Enter Amount'})
		}

class DebitForm(forms.ModelForm):
	class Meta:
		model = BankAccount
		fields = ('debitamt',)
		widgets = {
			'debitamt': forms.NumberInput(attrs={'class':'form-control','placeholder':'Enter Amount'})
		}

class LoanForm(forms.ModelForm):
	class Meta:
		model = BankAccount
		fields = ('loan',)
		widgets = {
			'loan': forms.NumberInput(attrs={'class':'form-control','placeholder':'Enter Amount'})
		}