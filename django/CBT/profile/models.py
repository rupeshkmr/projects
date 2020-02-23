from django.db import models
from accounts.models import User

class UserProfile(models.Model):
    user      = models.ForeignKey(User, on_delete=models.CASCADE)
    name      = models.CharField(max_length=255, blank=True)
    updated = models.BooleanField(default=False)

    def __str__(self):
        return self.user.email
# User.profile = property(lambda u: UserProfile.objects.get_or_create(user=u)[0])

