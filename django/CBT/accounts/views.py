from django.contrib.auth import authenticate , login , get_user_model , logout
from django.http import HttpResponse
from django.contrib.auth.decorators import user_passes_test
from .models import User
from profile.models import UserProfile
from django.shortcuts import render,redirect
from django.utils.decorators import method_decorator
from bank.models import BankAccount
from .forms import RegisterForm,LoginForm
from django.urls import reverse_lazy,reverse
from django.views.generic.edit import CreateView,UpdateView
def change_password(request):
    if request.user.is_authenticated:
        if request.method == 'POST':
            form = PasswordChangeForm(request.user, request.POST)
            if form.is_valid():
                user = form.save()
                update_session_auth_hash(request, user)  # Important!
                messages.success(request, 'Your password was successfully updated!')
                return redirect('profile:user-profile')
            else:
                messages.error(request, 'Please correct the error below.')
        else:
            form = PasswordChangeForm(request.user)
        return render(request, 'accounts/change_password.html', {
            'form': form
        })
    else:
        return redirect(reverse_lazy("login"))

def login_page(request):
    if (request.user.is_authenticated):
        return redirect("/")
    form=LoginForm(request.POST or None)
    context = {"form": form}
    if form.is_valid():
        username=form.cleaned_data.get("username")
        password=form.cleaned_data.get("password")
        user=authenticate(request,username=username,password=password)
        print(user)
        if user is not None:
                try:
                    profile = UserProfile.objects.get(user=user)
                    login(request,user)
                    context['form']=LoginForm()
                    return redirect(reverse_lazy("profile:profile-page"))
                except:
                    return HttpResponse("Please Register Yourself first<a href="">Go Back</a>")

        context['form']=LoginForm()
        context['error']="Please enter correct username or password"
        context['failed'] = "/static/failed.jpg"
    return render(request,"auth/login.html",context)

class ActivateAccount(UpdateView):
    @method_decorator(user_passes_test(lambda u: u.is_admin))
    def dispatch(self, *args, **kwargs):
         return super().dispatch(*args, **kwargs)
    model = User
    template_name = 'accounts/activate-account.html'
    fields = []
    def form_valid(self, form):
        obj = form.save(commit=False)
        obj.acc_on = True
        profile = UserProfile.objects.get(user=obj)
        account = BankAccount.objects.create(user=profile)
        account.save()
        profile.save()
        obj.save()
        return redirect(reverse_lazy("profile:confirm-profile"))
    success_url = reverse_lazy("profile:confirm-profile")


def logout_page(request,*args,**kwargs):
     if request.user.is_authenticated:
        logout(request,*args,**kwargs)
        return redirect('accounts:login')
     else:
        return redirect('accounts:login')
class RegisterView(CreateView):
    form_class = RegisterForm
    template_name = 'auth/register.html'

    def form_invalid(self, form):
        super(RegisterView, self).form_invalid(form)
        return render(self.request, self.template_name,
                      self.get_context_data(form=form))

    def get_context_data(self, **kwargs):
        ctx = super(RegisterView, self).get_context_data(**kwargs)
        try:
            if (self.request.POST['password1'] != self.request.POST['password2']):
                ctx['error'] = "Passwords donot match"
            if (User.objects.get(email=self.request.POST['email']) is None):
                pass
            else:
                ctx['eerror'] = "Email already taken"
        except:
            pass
        return ctx

    def form_valid(self, form):
        obj = form.save(commit=True)
        profile = UserProfile.objects.create(user=obj)
        obj.save()
        login(self.request,obj)
        return redirect(reverse('profile:update-user-profile',kwargs={'pk':profile.id}))
    success_url = '/login/'
