from django.urls import  include, path
from .views import BankDetails, Invest, Debit, Loan, Credit


urlpatterns = [
    path('bankdetails/<int:pk>/', BankDetails.as_view(), name='bankdetails'),
    path('credit/<int:pk>/', Credit.as_view(), name='credit'),
    path('debit/<int:pk>/', Debit.as_view(), name='debit'),
    path('loan/<int:pk>/', Loan.as_view(), name='loan'),
    path('invest/<int:pk>/', Invest.as_view(), name='invest'),
]

