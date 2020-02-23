from django.shortcuts import render
from django.contrib.auth.models import User
from django.http import Http404
from django.contrib.auth.decorators import login_required
from .forms import UserProfileForm
from django.urls import reverse_lazy,reverse
from django.template.context_processors import csrf
from django.http import HttpResponseRedirect,HttpResponse
from django.views.generic.edit import CreateView,UpdateView,DeleteView,FormView
from django.shortcuts import redirect
from django.utils.decorators import method_decorator
from django.contrib.auth.decorators import user_passes_test
from django.views.generic import ListView, DetailView
from .models import UserProfile
from bank.models import Bank, BankAccount
from django.contrib.auth import authenticate , login , get_user_model , logout
User = get_user_model()

class ConfirmProfile(ListView):
    @method_decorator(user_passes_test(lambda u:  u.is_admin))
    def dispatch(self, *args, **kwargs):
        return super().dispatch(*args, **kwargs)

    template_name = 'user-profile/confirm_profile.html'
    def get_queryset(self):
        queryset = UserProfile.objects.all()
        return queryset
    def get_queryset2(self):
        return User.objects.filter(acc_on=False)
    def get_context_data(self, **kwargs):
        context = super(ConfirmProfile, self).get_context_data(**kwargs)
        context['user_list'] = self.get_queryset2()
        # And so on for more models
        return context

@login_required
def user_profile(request):
    if request.method == 'POST':
        form = UserProfileForm(request.POST, instance=request.user.profile)
        if form.is_valid():
            form.save()
            return HttpResponseRedirect('/')
    else:
        user = request.user
        profile = user.profile
        form = UserProfileForm(instance=profile)

    args = {}
    args.update(csrf(request))
    args['form'] = form
    return  redirect(reverse('profile:update-user-profile',kwargs={'pk':profile.id}))

class UpdateUserProfile(UpdateView):
    @method_decorator(user_passes_test(lambda u: u.is_authenticated))
    def dispatch(self, *args, **kwargs):
        return super().dispatch(*args, **kwargs)

    template_name = 'user-profile/update-profile.html'
    model = UserProfile
    fields = ['name']
    success_url = reverse_lazy('profile:profile-page')

def error(request):
    return render(request,'user-profile/error.html',{})
User = get_user_model()
class ProfilePage(ListView):
    @method_decorator(user_passes_test(lambda u: u.is_authenticated))# and u.is_staff==False))
    def dispatch(self, *args, **kwargs):
        return super().dispatch(*args, **kwargs)

    template_name = 'user-profile/profile-page.html'


    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        if self.request.user.acc_on is True:
            context['bankaccount'] = BankAccount.objects.get(user=UserProfile.objects.get(user=self.request.user))
        context['bank'] = Bank.objects.first()
        return context

    def get_queryset(self):
        query = None
        query = UserProfile.objects.filter(user=self.request.user)
        if(query.first().name==""):
            return redirect(reverse('profile:UpdateUserProfile', kwargs={'pk': query.first().id.id}))
        return query

