# from django.contrib.auth.models import User, Group

from rest_framework import viewsets
from .models import ResidentIncome
from .serializers import ResidentIncomeSerializer

class ResidentIncomeViewSet(viewsets.ModelViewSet):
    queryset = ResidentIncome.objects.all()
    serializer_class = ResidentIncomeSerializer