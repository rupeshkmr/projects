from django.db import models
from profile.models import UserProfile
class Bank(models.Model):
	amount          = models.IntegerField(default=0)
	totalinvested   = models.IntegerField(default=0)

	def __str__(self):
		return str(self.amount)

class BankAccount(models.Model):
	user        = models.ForeignKey(UserProfile,on_delete=models.CASCADE)
	investment  = models.IntegerField(default=0)
	creditamt   = models.IntegerField(default=0)
	lastcredit  = models.IntegerField(default=0)
	debitamt    = models.IntegerField(default=0)
	lastdebit   = models.IntegerField(default=0)
	returnamt    = models.IntegerField(default=0)
	lastreturn  = models.IntegerField(default=0)
	investno    = models.IntegerField(default=0)
	shouldinvest= models.BooleanField(default=False)
	loan        = models.IntegerField(default=0)
	loan_date   = models.DateField(blank=True,null=True)
	invest_date = models.DateField(blank=True, null=True)
	return_date = models.DateField(blank=True,null=True)

	def __str__(self):
		return self.user.name
